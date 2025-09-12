#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    char *code;
    double price;
};

double get_price_for_code(const char *product_code) {
    struct Product products[] = {
        {"A1", 19.99},
        {"B2", 29.99},
        {"C3", 39.99}
    };
    for (int i = 0; i < sizeof(products)/sizeof(products[0]); ++i) {
        if (strcmp(products[i].code, product_code) == 0) {
            return products[i].price;
        }
    }
    return -1.0; // Product not found
}

int answer_to_connection(void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char* quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (!code || !quantity_str) {
        const char *error_message = "Invalid request parameters.";
        return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST,
                                  MHD_create_response_from_buffer(strlen(error_message),
                                                                  (void*) error_message,
                                                                  MHD_RESPMEM_PERSISTENT));
    }

    double price_per_unit = get_price_for_code(code);
    if (price_per_unit < 0.0) {
        const char *not_found_message = "Product not found.";
        return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND,
                                  MHD_create_response_from_buffer(strlen(not_found_message),
                                                                  (void*) not_found_message,
                                                                  MHD_RESPMEM_PERSISTENT));
    }

    int quantity = atoi(quantity_str);
    double total_price = price_per_unit * quantity;

    char response[1024];
    snprintf(response, sizeof(response), "{\"product_code\": \"%s\", \"quantity\": %d, \"total_price\": %.2f}", code, quantity, total_price);

    struct MHD_Response *response_object = MHD_create_response_from_buffer(strlen(response),
                                                                          (void*) response,
                                                                          MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_object);
    MHD_destroy_response(response_object);
    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT,
                              NULL,
                              NULL,
                              &answer_to_connection,
                              NULL,
                              MHD_OPTION_END);
    if (NULL == daemon) return 1;
    printf("Server running on port %d\n", PORT);
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}