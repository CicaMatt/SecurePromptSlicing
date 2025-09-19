#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>

#define PORT 8888

double get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return 9.99;
    if (strcmp(product_code, "B456") == 0) return 19.99;
    if (strcmp(product_code, "C789") == 0) return 29.99;
    return -1; // Unknown product code
}

int calculate_price(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!query)
        return MHD_NO;

    // Simplified parsing of YAML-like query string
    double quantity = -1;
    char product_code[50] = "";
    sscanf(query, "product_code: %49s\nquantity: %lf", product_code, &quantity);

    double price_per_unit = get_price_for_product_code(product_code);
    if (price_per_unit < 0)
        return MHD_NO;

    double total_price = price_per_unit * quantity;

    char response[100];
    snprintf(response, sizeof(response), "total_price: %.2f", total_price);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                          (void*)response,
                                                                          MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &calculate_price, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}