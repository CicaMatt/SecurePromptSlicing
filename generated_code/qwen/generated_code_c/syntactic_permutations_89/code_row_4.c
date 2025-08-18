#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

static struct MHD_Response *create_response(const char *data) {
    return MHD_create_response_from_buffer(strlen(data), (void *)data, MHD_RESPMEM_PERSISTENT);
}

double get_price_for_product_code(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Product not found
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        *con_cls = connection;
        return MHD_YES;
    }

    *con_cls = NULL;

    double total_price = -1;
    char response[256];
    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "product_code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code && quantity_str) {
        double price_per_unit = get_price_for_product_code(product_code);
        int quantity = atoi(quantity_str);

        if (price_per_unit >= 0)
            total_price = price_per_unit * quantity;
    }

    if (total_price < 0) {
        snprintf(response, sizeof(response), "Price not found for the given product code or invalid quantity.");
    } else {
        snprintf(response, sizeof(response), "Total price: %.2f", total_price);
    }

    struct MHD_Response *response_struct = create_response(response);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_struct);

    MHD_destroy_response(response_struct);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);

    return 0;
}