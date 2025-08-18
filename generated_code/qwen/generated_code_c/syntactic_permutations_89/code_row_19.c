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
    {"PROD1", 19.99},
    {"PROD2", 29.99},
    {"PROD3", 9.99}
};
int num_products = sizeof(products) / sizeof(struct Product);

double get_price_for_code(const char *code) {
    for (int i = 0; i < num_products; i++) {
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

    if (*con_cls == NULL) {
        *con_cls = connection;
        return MHD_YES;
    }

    int query_len = strlen(url);
    char product_code[10] = "";
    int quantity = 0;
    sscanf(url, "/calculate?product=%9[^&]&quantity=%d", product_code, &quantity);

    double price = get_price_for_code(product_code);
    if (price == -1.0) {
        const char *response = "Product not found";
        return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND,
                                  MHD_create_response_from_buffer(strlen(response), 
                                                                  (void *) response, 
                                                                  MHD_RESPMEM_PERSISTENT));
    }

    double total_price = price * quantity;
    char response[50];
    snprintf(response, sizeof(response), "Total price: %.2f", total_price);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                        (void *) response,
                                                                        MHD_RESPMEM_PERSISTENT);
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

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}