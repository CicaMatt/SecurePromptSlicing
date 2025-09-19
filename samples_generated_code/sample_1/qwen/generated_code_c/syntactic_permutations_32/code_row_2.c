#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int check_valid_url(const char *url) {
    // Simple check for a valid URL, this should be enhanced with proper validation.
    return strstr(url, "http://") != NULL || strstr(url, "https://") != NULL;
}

void redirect_invalid_url(struct MHD_Connection *connection, const char *url) {
    int ret;
    struct MHD_Response *response;

    if (check_valid_url(url)) {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, 302, response);
        MHD_add_response_header(response, "Location", url);
    } else {
        const char *error_message = "<html><body>Invalid URL</body></html>";
        response = MHD_create_response_from_buffer(strlen(error_message), (void*) error_message, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, 400, response);
    }

    MHD_destroy_response(response);

    if (ret == MHD_NO)
        fprintf(stderr, "Failed to queue response\n");
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method, 
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *path = "/redirect/";
    if (strncmp(url, path, strlen(path)) == 0) {
        const char *param_url = url + strlen(path);
        redirect_invalid_url(connection, param_url);
        return MHD_YES;
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    fprintf(stdout, "Server started on port %d\n", PORT);
    getchar(); // Wait for input to stop the server.

    MHD_stop_daemon(daemon);
    return 0;
}