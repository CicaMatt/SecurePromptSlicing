#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 14.99;
    if (strcmp(product_code, "C789") == 0) return 19.99;
    return -1.0; // Invalid product code
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "qty");

    if (!product_code || !quantity_str) {
        char response[100] = "<h1>Missing product code or quantity</h1>";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
        MHD_destroy_response(resp);
        return ret;
    }

    double quantity = atof(quantity_str);
    if (quantity <= 0) {
        char response[100] = "<h1>Invalid quantity</h1>";
        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, resp);
        MHD_destroy_response(resp);
        return ret;
    }

    double price = get_price(product_code) * quantity;

    char response[100];
    sprintf(response, "<h1>Total Price: %.2f</h1>", price);

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "Failed to start daemon\n");
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}