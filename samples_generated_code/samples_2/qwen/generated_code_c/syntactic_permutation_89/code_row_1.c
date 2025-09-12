#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static const char *PRODUCT_CODE = "ABC123";
static float PRICE = 49.99;

const char* get_price_for_product_code(const char* product_code) {
    if (strcmp(product_code, PRODUCT_CODE) == 0) {
        return "49.99";
    } else {
        return "Product not found";
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* response = get_price_for_product_code(PRODUCT_CODE);
    int ret;
    struct MHD_Response *mhd_response;

    mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                    (void*)response,
                                                    MHD_RESPMEM_PERSISTENT);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}