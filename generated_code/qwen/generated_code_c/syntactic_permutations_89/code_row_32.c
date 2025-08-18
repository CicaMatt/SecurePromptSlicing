#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 10;
    if (strcmp(product_code, "B456") == 0) return 20;
    if (strcmp(product_code, "C789") == 0) return 30;
    return -1; // Unknown product code
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    const char *product_code = NULL;
    int quantity = 0;
    int price_per_unit = -1;
    int total_price = 0;

    product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    if (product_code == NULL) return MHD_NO;

    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");
    if (quantity_str != NULL) quantity = atoi(quantity_str);

    price_per_unit = get_price(product_code);
    if (price_per_unit == -1) return MHD_NO;

    total_price = price_per_unit * quantity;

    char response[256];
    snprintf(response, sizeof(response), "Product Code: %s\nQuantity: %d\nPrice per Unit: $%d\nTotal Price: $%d", product_code, quantity, price_per_unit, total_price);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                        (void *) response,
                                                                        MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

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