#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1; // Invalid product code
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "product");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (!product_code || !quantity_str) {
        const char *error_msg = "<h1>Missing product code or quantity</h1>";
        return MHD_daemon_response(connection, 400, error_msg);
    }

    int quantity = atoi(quantity_str);
    double price_per_unit = get_price(product_code);
    if (price_per_unit < 0) {
        const char *error_msg = "<h1>Invalid product code</h1>";
        return MHD_daemon_response(connection, 400, error_msg);
    }

    double total_price = price_per_unit * quantity;
    char response[256];
    snprintf(response, sizeof(response), "Total Price: %.2f", total_price);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *)response,
                                                                         MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    return ret;
}

int main(void) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD,
                              PORT,
                              NULL, NULL,
                              &handle_request, NULL,
                              MHD_OPTION_END);

    if (!daemon) {
        fprintf(stderr, "Failed to start daemon\n");
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}

int MHD_daemon_response(struct MHD_Connection *connection, int status_code, const char *content) {
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(content),
                                                (void *) content,
                                                MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    int ret = MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
    return ret;
}