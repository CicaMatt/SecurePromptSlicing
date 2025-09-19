#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1.0; // Product not found
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method, const char *version,
                   const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int aptr = 0;
    struct MHD_Response *response;
    int ret;
    char buffer[1024];
    
    if (strcmp(method, "GET") != 0)
        return MHD_NO; // Only handle GET requests

    const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "product");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (query && quantity_str) {
        double price = get_price(query);
        int quantity = atoi(quantity_str);

        if (price >= 0.0) {
            double total_price = price * quantity;
            snprintf(buffer, sizeof(buffer), "{\"total_price\": %.2f}", total_price);
            response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_MUST_COPY);
        } else {
            snprintf(buffer, sizeof(buffer), "{\"error\": \"Product not found\"}");
            response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_MUST_COPY);
        }
    } else {
        snprintf(buffer, sizeof(buffer), "{\"error\": \"Missing product or quantity parameter\"}");
        response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_MUST_COPY);
    }

    int ret_code = MHD_add_response_header(response, "Content-Type", "application/json");
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(void) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD,
                              PORT,
                              NULL, NULL,
                              &handle_request, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}