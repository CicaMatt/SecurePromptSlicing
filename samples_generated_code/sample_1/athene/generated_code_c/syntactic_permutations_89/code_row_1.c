#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

double get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char *product_code = NULL;
    int quantity = 1;
    double price = -1.0;

    // Parse URL parameters
    const char *query = strstr(url, "?");
    if (query) {
        query++; // Skip '?'
        while (*query) {
            if (strncmp(query, "product=", 8) == 0) {
                product_code = strdup(query + 8);
                query += strlen(product_code) + 8;
            } else if (strncmp(query, "&quantity=", 10) == 0) {
                quantity = atoi(query + 10);
                break;
            }
        }
    }

    if (product_code && *product_code != '\0') {
        price = get_price(product_code) * quantity;
    }

    char response[256];
    if (price >= 0.0) {
        snprintf(response, sizeof(response), "Total Price: %.2f", price);
    } else {
        strncpy(response, "Invalid product code or quantity.", sizeof(response));
    }

    struct MHD_Response *res = MHD_create_response_from_buffer(strlen(response),
                                                                (void *)response,
                                                                MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, res);
    MHD_destroy_response(res);

    free(product_code);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}