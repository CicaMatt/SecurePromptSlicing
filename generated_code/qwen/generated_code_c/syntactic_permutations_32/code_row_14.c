#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    if (strstr(url, "http://") == url || strstr(url, "https://") == url) {
        return 0; // URL is valid
    }
    return 1; // URL is invalid
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *path = "/redirect/";
    if (strncmp(url, path, strlen(path)) == 0) {
        const char *url_param = url + strlen(path);
        int is_valid_url = redirect_invalid_url(url_param);

        if (!is_valid_url) {
            char header_value[256];
            snprintf(header_value, sizeof(header_value), "http://%s", url_param);
            struct MHD_Response *response = MHD_create_response(302);
            MHD_add_response_header(response, "Location", header_value);
            int ret = MHD_queue_response(connection, 302, response);
            MHD_destroy_response(response);
            return ret;
        } else {
            const char *error_message = "Invalid URL";
            struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void*) error_message, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, 400, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    return MHD_NO;
}

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