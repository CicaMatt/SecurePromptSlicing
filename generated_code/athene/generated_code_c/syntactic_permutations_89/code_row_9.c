#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct MHD_Daemon *daemon;

const char *get_price(const char *product_code) {
    if (strcmp(product_code, "A123") == 0) return "10.99";
    if (strcmp(product_code, "B456") == 0) return "15.50";
    if (strcmp(product_code, "C789") == 0) return "7.25";
    return "0.00";
}

int calculate_price(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    const char *product_code = NULL;
    const char *quantity_str = NULL;
    int quantity = 0;

    struct MHD_GETArgumentsIterator iter;
    if (MHD_get_argument_iterator(connection, &iter)) return MHD_NO;
    while (MHD_get_next_argument(&iter, NULL, &product_code) &&
           MHD_get_next_argument(&iter, NULL, &quantity_str)) {
        quantity = atoi(quantity_str);
    }

    double price = atof(get_price(product_code));
    char response[50];
    snprintf(response, sizeof(response), "%.2f", price * quantity);

    struct MHD_Response *resp;
    resp = MHD_create_response_from_buffer(strlen(response),
                                            (void *)response,
                                            MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
    return ret;
}

int main() {
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &calculate_price, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}