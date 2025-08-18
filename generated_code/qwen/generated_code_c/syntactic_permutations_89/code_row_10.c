#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    const char* code;
    double price;
};

static struct Product products[] = {
    {"A1", 29.99},
    {"B2", 45.50},
    {"C3", 19.75}
};

#define NUM_PRODUCTS (sizeof(products) / sizeof(struct Product))

double get_price(const char* code, int quantity) {
    for (size_t i = 0; i < NUM_PRODUCTS; ++i) {
        if (strcmp(products[i].code, code) == 0) {
            return products[i].price * quantity;
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

    const char* code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char* quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (!code || !quantity_str) {
        return MHD_NO;
    }

    int quantity = atoi(quantity_str);
    double price = get_price(code, quantity);

    char response[1024];
    if (price >= 0) {
        snprintf(response, sizeof(response), "{\"product_code\": \"%s\", \"quantity\": %d, \"total_price\": %.2f}", code, quantity, price);
    } else {
        snprintf(response, sizeof(response), "{\"error\": \"Product not found\"}");
    }

    struct MHD_Response* response_obj = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    return ret;
}

int main() {
    struct MHD_Daemon* daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}