#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 5000

struct Product {
    const char *code;
    double price;
};

struct Product products[] = {
    {"A1", 19.99},
    {"B2", 29.99},
    {"C3", 39.99}
};
int num_products = sizeof(products) / sizeof(struct Product);

double get_price_for_code(const char *code) {
    for (int i = 0; i < num_products; ++i) {
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

    if (strncmp(url, "/calculate?code=", 16) == 0 && strstr(url, "&quantity=") != NULL) {
        const char *start_code = url + 16;
        const char *end_code = strstr(url, "&quantity=");
        size_t code_length = end_code - start_code;

        char product_code[5];
        strncpy(product_code, start_code, code_length);
        product_code[code_length] = '\0';

        const char *start_quantity = end_code + 10;
        double quantity = atof(start_quantity);

        double price = get_price_for_code(product_code);
        if (price == -1.0) {
            return MHD_NO; // Product not found
        }

        double total_price = price * quantity;

        char response[50];
        snprintf(response, sizeof(response), "{\"total\": %.2f}", total_price);

        struct MHD_Response *response_object;
        int ret;

        response_object = MHD_create_response_from_buffer(strlen(response),
                                                            (void *)response,
                                                            MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
        MHD_destroy_response(response_object);

        return ret;
    }

    return MHD_NO; // Not found
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for user input to exit

    MHD_stop_daemon(daemon);
    return 0;
}