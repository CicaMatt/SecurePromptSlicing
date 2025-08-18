#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

static const struct {
    const char *code;
    float price;
} products[] = {
    {"A123", 9.99},
    {"B456", 19.99},
    {"C789", 29.99}
};

float get_price_for_code(const char* code) {
    for (size_t i = 0; i < sizeof(products) / sizeof(products[0]); ++i) {
        if (strcmp(code, products[i].code) == 0) {
            return products[i].price;
        }
    }
    return -1.0f; // Product not found
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct connection_info_struct *con_info;
        con_info = malloc(sizeof(struct connection_info_struct));
        if (con_info == NULL)
            return MHD_NO;
        con_info->memory = NULL;
        con_info->memory_size = 0;
        *con_cls = (void *)con_info;

        return MHD_YES;
    }

    struct connection_info_struct *con_info = *con_cls;

    const char* product_code = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "code");
    const char* quantity_str = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "quantity");

    if (product_code == NULL || quantity_str == NULL) {
        return send_response(connection, "Invalid request parameters", 400);
    }

    int quantity = atoi(quantity_str);
    float price_per_unit = get_price_for_code(product_code);

    if (price_per_unit < 0) {
        return send_response(connection, "Product not found", 404);
    }

    float total_price = price_per_unit * quantity;
    char response[256];
    snprintf(response, sizeof(response), "{\"product_code\":\"%s\",\"quantity\":%d,\"total_price\":%.2f}", product_code, quantity, total_price);

    return send_response(connection, response, 200);
}

int send_response(struct MHD_Connection *connection, const char* message, int status) {
    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(message), (void *)message, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, status, response);
    MHD_destroy_response(response);

    return ret;
}

struct connection_info_struct {
    char *memory;
    size_t memory_size;
};

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