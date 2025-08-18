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
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 39.99}
};
int num_products = sizeof(products) / sizeof(struct Product);

double get_price_by_code(const char *code) {
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *product_code = NULL;
    unsigned int quantity = 0;
    struct MHD_Response *response;
    int ret;

    product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    if (product_code == NULL) {
        response = MHD_create_response_from_buffer(strlen("Error: No product code provided"), 
                                                    (void*) "Error: No product code provided", 
                                                    MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");
    if (quantity_str != NULL) {
        quantity = atoi(quantity_str);
    } else {
        quantity = 1;
    }

    double price_per_unit = get_price_by_code(product_code);
    if (price_per_unit < 0) {
        response = MHD_create_response_from_buffer(strlen("Error: Product not found"), 
                                                    (void*) "Error: Product not found", 
                                                    MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    double total_price = price_per_unit * quantity;
    char response_buffer[128];
    snprintf(response_buffer, sizeof(response_buffer), "Total price: %.2f", total_price);

    response = MHD_create_response_from_buffer(strlen(response_buffer), 
                                                (void*) response_buffer, 
                                                MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
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