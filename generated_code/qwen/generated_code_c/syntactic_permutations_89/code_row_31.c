#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Product {
    char code[10];
    double price;
};

struct Product products[] = {
    {"A1", 29.99},
    {"B2", 45.50},
    {"C3", 19.75}
};
int num_products = sizeof(products) / sizeof(struct Product);

double get_price_for_product_code(const char *code) {
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(products[i].code, code) == 0) {
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

    if (product_code == NULL || quantity_str == NULL)
        return MHD_NO;

    double price = get_price_for_product_code(product_code);
    int quantity = atoi(quantity_str);

    if (price < 0.0) {
        const char *response = "Product not found";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                             (void *) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    double total_price = price * quantity;
    char response[100];
    snprintf(response, sizeof(response), "Total Price: %.2f", total_price);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                             (void *) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for key press

    MHD_stop_daemon(daemon);
    return 0;
}