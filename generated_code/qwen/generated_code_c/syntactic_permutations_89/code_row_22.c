#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

static int get_price(const char* product_code) {
    if (strcmp(product_code, "P1") == 0) return 100;
    if (strcmp(product_code, "P2") == 0) return 200;
    return -1; // Product not found
}

static int handler(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* product_code = strchr(url, '?');
    if (!product_code || strlen(product_code) < 3)
        return MHD_NO;
    product_code += 1; // Skip the '?' character

    int price = get_price(product_code);
    if (price == -1) {
        const char *not_found_msg = "Product not found";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(not_found_msg),
                                                                        (void*) not_found_msg,
                                                                        MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }

    char buffer[1024];
    snprintf(buffer, sizeof(buffer), "{\"product_code\":\"%s\", \"price\": %d}", product_code, price);
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer),
                                                                    (void*) buffer,
                                                                    MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}