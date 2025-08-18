#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    char *code;
    double price;
};

struct Product products[] = {
    {"A1", 29.99},
    {"B2", 49.99},
    {"C3", 19.99}
};

int num_products = sizeof(products) / sizeof(struct Product);

double get_price_for_product_code(const char *code) {
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1; // Product not found
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    double total_price = -1;
    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code != NULL && quantity_str != NULL) {
        int quantity = atoi(quantity_str);
        double price_per_unit = get_price_for_product_code(product_code);
        if (price_per_unit != -1) {
            total_price = price_per_unit * quantity;
        }
    }

    char response[256];
    snprintf(response, sizeof(response), "{\"total_price\": %.2f}", total_price);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *)response,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}