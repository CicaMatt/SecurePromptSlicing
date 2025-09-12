#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct MHD_Daemon *daemon;

double get_product_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return 19.99;
    if (strcmp(product_code, "B456") == 0) return 29.99;
    if (strcmp(product_code, "C789") == 0) return 39.99;
    return -1; // Invalid product code
}

int calculate_price(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method, const char *version,
                    const char *upload_data, size_t *upload_data_size, void **con_cls) {
    static int aptr = 0;
    const char *product_code = NULL;
    const char *quantity_str = NULL;
    double quantity = 1.0;

    struct MHD_Response *response;
    int ret;
    char buffer[1024];

    if (MHD_NO == MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, 
                                            &product_code, "product_code")) {
        product_code = "";
    }
    if (MHD_NO == MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, 
                                            &quantity_str, "quantity")) {
        quantity_str = "1";
    }

    quantity = atof(quantity_str);
    double price = get_product_price(product_code) * quantity;

    if (price < 0) {
        snprintf(buffer, sizeof(buffer), "{\"error\": \"Invalid product code\"}");
    } else {
        snprintf(buffer, sizeof(buffer), "{\"total\": %.2f}", price);
    }

    response = MHD_create_response_from_buffer(strlen(buffer),
                                               (void *)buffer,
                                               MHD_RESPMEM_PERSISTENT);
    ret = MHD_add_response_header(response, "Content-Type", "application/json");
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(void) {
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &calculate_price, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}