#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

struct Product {
    char *code;
    double price;
};

struct Product products[] = {
    {"A123", 9.99},
    {"B456", 19.99},
    {"C789", 29.99}
};
#define NUM_PRODUCTS (sizeof(products) / sizeof(products[0]))

double get_price_by_code(const char *code) {
    for (size_t i = 0; i < NUM_PRODUCTS; ++i) {
        if (strcmp(code, products[i].code) == 0) {
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

    if (*con_cls == NULL) {
        *con_cls = connection;
        return MHD_YES;
    }

    if (strstr(url, "/calculate?code=") == url) {
        const char *query = strstr(url, "?code=");
        query += strlen("?code=");
        const char *end_of_code = strchr(query, '&');
        size_t code_len = end_of_code ? (size_t)(end_of_code - query) : strlen(query);
        char code[10];
        strncpy(code, query, code_len);
        code[code_len] = '\0';

        double price = get_price_by_code(code);
        if (price < 0) {
            const char *response = "Product not found";
            int response_size = strlen(response);
            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void*)response, MHD_RESPMEM_PERSISTENT);
            return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, mhd_response);
        }

        const char *quantity_str = strstr(url, "&quantity=");
        if (!quantity_str) {
            const char *error_response = "Quantity parameter is missing";
            int response_size = strlen(error_response);
            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void*)error_response, MHD_RESPMEM_PERSISTENT);
            return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        }
        quantity_str += strlen("&quantity=");
        int quantity = atoi(quantity_str);

        char response[50];
        snprintf(response, sizeof(response), "Total price: %.2f", price * quantity);
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    }

    const char *error_response = "Invalid request";
    int response_size = strlen(error_response);
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void*)error_response, MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}