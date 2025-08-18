#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 5000

struct Product {
    char code[10];
    double price;
};

const struct Product products[] = {
    {"P001", 9.99},
    {"P002", 19.99},
    {"P003", 4.99}
};

#define NUM_PRODUCTS (sizeof(products) / sizeof(products[0]))

double find_product_price(const char *product_code) {
    for (size_t i = 0; i < NUM_PRODUCTS; ++i) {
        if (strcmp(product_code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code == NULL || quantity_str == NULL)
        return MHD_NO;

    double price = find_product_price(product_code);
    int quantity = atoi(quantity_str);

    if (price < 0.0 || quantity <= 0)
        return MHD_NO;

    char response[128];
    snprintf(response, sizeof(response), "Total: %.2f", price * quantity);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *)response,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}