#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    char *code;
    double price;
};

static struct Product products[] = {
    {"P1", 19.99},
    {"P2", 29.99},
    {"P3", 49.99}
};

#define PRODUCT_COUNT (sizeof(products) / sizeof(struct Product))

double get_price_for_code(const char *product_code) {
    for (int i = 0; i < PRODUCT_COUNT; ++i) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return -1 if the product code is not found
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                              const char *url, const char *method,
                              const char *version, const char *upload_data,
                              size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code == NULL || quantity_str == NULL)
        return MHD_NO;

    double price = get_price_for_code(product_code);
    int quantity = atoi(quantity_str);

    if (price < 0 || quantity <= 0)
        return MHD_NO;

    double total_price = price * quantity;
    char response[256];
    snprintf(response, sizeof(response), "Total price for %d units of product %s: %.2f", quantity, product_code, total_price);

    struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}