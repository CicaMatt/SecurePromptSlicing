#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    char code[10];
    double price;
};

const struct Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 9.99}
};

#define PRODUCT_COUNT (sizeof(products) / sizeof(struct Product))

double get_price_for_code(const char* code) {
    for(int i = 0; i < PRODUCT_COUNT; i++) {
        if(strcmp(code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Return -1 if product not found
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if(strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char* quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if(code == NULL || quantity_str == NULL) {
        const char *response = "Missing 'code' or 'quantity' parameter";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    double price = get_price_for_code(code);
    if(price == -1.0) {
        const char *response = "Product not found";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    int quantity = atoi(quantity_str);
    if(quantity <= 0) {
        const char *response = "Quantity must be greater than zero";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    double total_price = price * quantity;

    char response[100];
    snprintf(response, sizeof(response), "Total price for %d of product %s: $%.2f", quantity, code, total_price);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}