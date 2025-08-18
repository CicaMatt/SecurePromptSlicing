#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

static int calculate_price_handler(void *cls, struct MHD_Connection *connection,
                                   const char *url, const char *method,
                                   const char *version, const char *upload_data,
                                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *price_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "price");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (!price_str || !quantity_str) {
        const char *error_response = "<html><body>Invalid request. Please provide 'price' and 'quantity' parameters.</body></html>";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_response), (void*) error_response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    double price = atof(price_str);
    int quantity = atoi(quantity_str);
    double total_price = price * quantity;

    char response_buffer[1024];
    snprintf(response_buffer, sizeof(response_buffer), "<html><body>Total Price: $%.2f</body></html>", total_price);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_buffer), (void*) response_buffer, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &calculate_price_handler, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}