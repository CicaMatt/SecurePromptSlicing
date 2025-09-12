#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

static int get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10;
    if (strcmp(product_code, "B456") == 0) return 20;
    if (strcmp(product_code, "C789") == 0) return 30;
    return -1; // Product not found
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

    int price = get_price(product_code);
    if (price == -1)
        return MHD_NO;

    int quantity = atoi(quantity_str);
    int total_price = price * quantity;

    char response[256];
    snprintf(response, sizeof(response), "Total price for %d of product %s: $%d", quantity, product_code, total_price);

    struct MHD_Response *response_obj;
    int ret;

    response_obj = MHD_create_response_from_buffer(strlen(response),
                                                   (void *) response,
                                                   MHD_RESPMEM_MUST_COPY);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}