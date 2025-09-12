#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Product {
    char *code;
    float price;
};

struct Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 39.99}
};
#define NUM_PRODUCTS (sizeof(products) / sizeof(struct Product))

float get_price_for_product_code(const char *code) {
    for (int i = 0; i < NUM_PRODUCTS; i++) {
        if (strcmp(code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Return -1.0 to indicate product not found
}

void *answer_to_connection(void *cls, struct MHD_Connection *connection,
                           const char *url, const char *method,
                           const char *version, const char *upload_data,
                           size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return NULL;

    const char *product_code = strchr(url, '?');
    if (!product_code || strlen(product_code) < 3)
        return MHD_NO;

    product_code++; // Move past the '?' character
    float price = get_price_for_product_code(product_code);

    char response[256];
    if (price == -1.0f) {
        snprintf(response, sizeof(response), "Product not found");
    } else {
        snprintf(response, sizeof(response), "Price: $%.2f", price);
    }

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                        (void *) response,
                                                                        MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret == MHD_YES ? NULL : cls;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar(); // Wait for user input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}