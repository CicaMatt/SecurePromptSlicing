#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int check_valid_url(const char *url) {
    const char *prefix = "http://";
    return strncmp(url, prefix, strlen(prefix)) == 0 || 
           strncmp(url, "https://", 8) == 0;
}

void *redirect_invalid_url(void *cls, struct MHD_Connection *connection,
                           const char *url, const char *method,
                           const char *version, const char *upload_data,
                           size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return NULL;

    const char *path = MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, "url");
    if (!path || !check_valid_url(path)) {
        const char *response = "<html><body>Invalid URL</body></html>";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret ? con_cls : NULL;
    }

    struct MHD_Response *mhd_response = MHD_create_redirect_response(MHD_HTTP_FOUND, path);
    int ret = MHD_queue_response(connection, MHD_HTTP_FOUND, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret ? con_cls : NULL;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &redirect_invalid_url, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}