#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    const char *code;
    double price;
};

const struct Product products[] = {
    {"A1", 9.99},
    {"B2", 19.99},
    {"C3", 4.99}
};
const size_t num_products = sizeof(products) / sizeof(struct Product);

double get_price_for_code(const char *product_code) {
    for (size_t i = 0; i < num_products; ++i) {
        if (strcmp(product_code, products[i].code) == 0) {
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

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (!product_code || !quantity_str) {
        return MHD_NO;
    }

    double price_per_unit = get_price_for_code(product_code);
    int quantity = atoi(quantity_str);

    if (price_per_unit < 0.0 || quantity <= 0) {
        const char *response = "{\"error\": \"Invalid product code or quantity\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    double total_price = price_per_unit * quantity;
    char response[100];
    snprintf(response, sizeof(response), "{\"product_code\": \"%s\", \"quantity\": %d, \"total_price\": %.2f}", product_code, quantity, total_price);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}