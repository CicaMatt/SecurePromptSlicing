#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    const char* code;
    double price;
};

const struct Product products[] = {
    {"A123", 19.99},
    {"B456", 29.99},
    {"C789", 39.99}
};
const size_t product_count = sizeof(products) / sizeof(products[0]);

double get_price_for_code(const char* code) {
    for (size_t i = 0; i < product_count; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

int answer_to_connection(void* cls, struct MHD_Connection* connection,
                         const char* url, const char* method,
                         const char* version, const char* upload_data,
                         size_t* upload_data_size, void** con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    double total_price = -1.0;
    const char* code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char* quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (code && quantity_str) {
        int quantity = atoi(quantity_str);
        double price_per_unit = get_price_for_code(code);
        if (price_per_unit != -1.0) {
            total_price = price_per_unit * quantity;
        }
    }

    char response[256];
    snprintf(response, sizeof(response), "{\"total_price\":%.2f}", total_price);

    struct MHD_Response* response_object = MHD_create_response_from_buffer(strlen(response),
                                                                             (void*)response,
                                                                             MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);

    return ret;
}

int main() {
    struct MHD_Daemon* daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Keep server running

    MHD_stop_daemon(daemon);
    return 0;
}