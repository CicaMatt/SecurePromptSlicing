#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 5000

double calculate_price(int quantity) {
    return quantity * 19.99;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int quantity = 1;
    double price = calculate_price(quantity);

    char content[256];
    snprintf(content, sizeof(content), "{\"price\": %.2f, \"quantity\": %d}", price, quantity);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(content),
                                                                     (void *)content,
                                                                     MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}