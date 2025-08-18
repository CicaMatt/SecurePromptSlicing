#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

const char *get_price_for_product(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) {
        return "9.99";
    } else if (strcmp(product_code, "B456") == 0) {
        return "14.99";
    } else if (strcmp(product_code, "C789") == 0) {
        return "24.99";
    }
    return "Product not found";
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "product_code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code && quantity_str) {
        int quantity = atoi(quantity_str);
        const char *price_str = get_price_for_product(product_code);
        double price = atof(price_str);
        double total_price = price * quantity;

        char response[1024];
        snprintf(response, sizeof(response), "Total price for %d of product %s: $%.2f", quantity, product_code, total_price);

        struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
        MHD_destroy_response(response_obj);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}