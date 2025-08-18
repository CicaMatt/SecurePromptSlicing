#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Product {
    const char* code;
    double price;
};

const struct Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 39.99}
};

#define NUM_PRODUCTS (sizeof(products) / sizeof(struct Product))

double get_price_by_code(const char* code) {
    for (size_t i = 0; i < NUM_PRODUCTS; ++i) {
        if (strcmp(code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    double total_price = -1.0;
    const char* product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char* quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code && quantity_str) {
        double price = get_price_by_code(product_code);
        int quantity = atoi(quantity_str);

        if (price != -1.0 && quantity > 0)
            total_price = price * quantity;
    }

    char response[50];
    snprintf(response, sizeof(response), "{\"total\": %.2f}", total_price);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                        (void*) strdup(response),
                                                                        MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}