#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 5000

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return -1.0; // Product not found
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) return MHD_NO;

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "product");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (!product_code || !quantity_str) {
        const char *error_page = "<html><body>Error: Missing parameters</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_page),
                                                                         (void *) error_page,
                                                                         MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    }

    int quantity = atoi(quantity_str);
    double price = get_price(product_code) * quantity;

    if (price < 0) {
        const char *error_page = "<html><body>Error: Invalid product code</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_page),
                                                                         (void *) error_page,
                                                                         MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    }

    char price_str[50];
    snprintf(price_str, sizeof(price_str), "Total Price: %.2f", price);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(price_str),
                                                                     (void *) price_str,
                                                                     MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL) return 1;

    while (1) {
        pause();
    }

    MHD_stop_daemon(daemon);
    return 0;
}