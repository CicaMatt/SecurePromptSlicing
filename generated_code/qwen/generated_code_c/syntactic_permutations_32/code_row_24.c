#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

int redirect_invalid_url(const char *url) {
    if (strstr(url, "example.com") != NULL) {
        return MHD_NO; // Continue processing the request
    } else {
        return MHD_YES; // Stop processing and return an error
    }
}

void send_response(struct MHD_Connection *connection, int status_code, const char *message) {
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(message), (void*) message, MHD_RESPMEM_PERSISTENT);
    MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *path = "/redirect/";
    if (strncmp(url, path, strlen(path)) == 0) {
        const char *target_url = url + strlen(path);
        if (!redirect_invalid_url(target_url)) {
            char redirect_message[256];
            snprintf(redirect_message, sizeof(redirect_message), "Redirecting to %s", target_url);
            MHD_add_response_header(MHD_create_response_from_buffer(strlen(redirect_message),
                                                                   (void*) redirect_message,
                                                                   MHD_RESPMEM_PERSISTENT),
                                    "Location",
                                    target_url);
            return MHD_queue_response(connection, MHD_HTTP_FOUND, NULL);
        } else {
            send_response(connection, MHD_HTTP_BAD_REQUEST, "Invalid URL");
        }
    } else {
        send_response(connection, MHD_HTTP_NOT_FOUND, "Not Found");
    }
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}