#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include "microhttpd.h"

#define PORT 5000

typedef struct {
    char *product_code;
    double price_per_unit;
} Product;

Product products[] = {
    {"P001", 10.99},
    {"P002", 23.50},
    {"P003", 5.75}
};

int num_products = sizeof(products) / sizeof(Product);

double get_product_price(const char *product_code) {
    for (int i = 0; i < num_products; ++i) {
        if (strcmp(products[i].product_code, product_code) == 0) {
            return products[i].price_per_unit;
        }
    }
    return -1.0; // Product not found
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0) {
        int ret;
        char *page;

        // Parse query
        struct MHD_PostProcessor *pp = NULL;
        char *product_code = NULL;
        long quantity = 1;

        pp = MHD_create_post_processor(connection, 1024, &parse_query_callback,
                                       (void *)&product_code);

        if (upload_data != NULL && upload_data_size != NULL) {
            ret = MHD_process_post_connection(pp, upload_data, *upload_data_size,
                                              upload_data_size);
            if (ret == MHD_YES)
                return MHD_YES;
            else if (ret == MHD_NO)
                return MHD_NO;
        }

        double price_per_unit = get_product_price(product_code);
        if (price_per_unit < 0) {
            page = "<html><body>Product not found</body></html>";
        } else {
            double total_price = price_per_unit * quantity;
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "%.2f", total_price);
            page = malloc(strlen("<html><body>") + strlen(buffer) +
                          strlen("</body></html>") + 1);
            sprintf(page, "<html><body>Total Price: $%s</body></html>", buffer);
        }

        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(page), (void *)page,
                                                   MHD_RESPMEM_MUST_COPY);
        int ret2 = MHD_queue_response(connection, MHD_HTTP_OK, response);

        MHD_destroy_response(response);
        free(page);

        if (pp != NULL)
            MHD_destroy_post_processor(pp);
    }

    return MHD_NO;
}

static void parse_query_callback(void *cls,
                                 enum MHD_ValueKind kind, const char *key,
                                 const char *value) {
    char **product_code = (char **)cls;

    if (strcmp(key, "code") == 0 && strcmp(kind, MHD_KEY_KIND_STRING) == 0) {
        *product_code = strdup(value);
    } else if (strcmp(key, "quantity") == 0 && strcmp(kind, MHD_KEY_KIND_NUMBER) == 0) {
        long quantity = strtol(value, NULL, 10);
        ((long *)cls)[1] = quantity;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                              PORT, NULL, NULL, &answer_to_connection, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}