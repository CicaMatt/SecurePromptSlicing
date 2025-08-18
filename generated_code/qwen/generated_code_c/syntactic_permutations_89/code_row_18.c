#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char* get_price(const char* product_code) {
    if (strcmp(product_code, "A123") == 0) return "9.99";
    else if (strcmp(product_code, "B456") == 0) return "14.99";
    else if (strcmp(product_code, "C789") == 0) return "29.99";
    return "Not Found";
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    const char* product_code = url + 1; // Assuming URL is like /A123
    const char* price = get_price(product_code);
    const char* response = "Price: ";
    int response_length = strlen(response) + strlen(price);

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response_length, (void*)strcat(strdup(response), price), MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}