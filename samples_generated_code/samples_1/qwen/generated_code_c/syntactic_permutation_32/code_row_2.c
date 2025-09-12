#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int check_valid_url(const char *url) {
    return url != NULL && strlen(url) > 0;
}

void redirect_invalid_url(struct MHD_Connection *connection, const char *url) {
    if (check_valid_url(url)) {
        struct MHD_Response *response = MHD_create_response(302);
        MHD_add_response_header(response, "Location", url);
        MHD_queue_response(connection, 302, response);
        MHD_destroy_response(response);
    } else {
        const char *error_message = "{\"error\": \"Invalid URL\"}";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_message), (void*) error_message, MHD_RESPMEM_PERSISTENT);
        MHD_add_response_header(response, "Content-Type", "application/json");
        MHD_queue_response(connection, 400, response);
        MHD_destroy_response(response);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *path = "/redirect/";
    if (strncmp(url, path, strlen(path)) == 0) {
        const char *url_param = url + strlen(path);
        redirect_invalid_url(connection, url_param);
        return MHD_YES;
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}