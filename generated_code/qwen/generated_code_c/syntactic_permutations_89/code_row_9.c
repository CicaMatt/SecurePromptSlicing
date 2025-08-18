#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    const char *code;
    double price;
};

static struct Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 39.99}
};

#define PRODUCT_COUNT (sizeof(products) / sizeof(struct Product))

double get_price_by_code(const char *code) {
    for (int i = 0; i < PRODUCT_COUNT; i++) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    double price = -1.0;
    int quantity = 1;

    const char *code_param = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    if (code_param) {
        price = get_price_by_code(code_param);
    }

    const char *quantity_param = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");
    if (quantity_param) {
        quantity = atoi(quantity_param);
    }

    double total_price = price * quantity;
    char response[256];
    snprintf(response, sizeof(response), "{\"price\":%.2f}", total_price);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                        (void*)response,
                                                                        MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
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