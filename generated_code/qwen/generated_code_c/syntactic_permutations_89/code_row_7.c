#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    char code[10];
    float price;
};

static struct Product products[] = {
    {"A001", 9.99},
    {"B002", 19.99},
    {"C003", 4.99}
};
#define PRODUCT_COUNT (sizeof(products) / sizeof(struct Product))

float get_price_by_code(const char *code) {
    for (int i = 0; i < PRODUCT_COUNT; ++i) {
        if (strcmp(code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Not found
}

static int handler(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char *quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code == NULL || quantity_str == NULL)
        return MHD_NO;

    float price_per_unit = get_price_by_code(product_code);
    int quantity = atoi(quantity_str);
    float total_price = price_per_unit * quantity;

    char response[100];
    snprintf(response, sizeof(response), "Total Price: %.2f", total_price);

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}