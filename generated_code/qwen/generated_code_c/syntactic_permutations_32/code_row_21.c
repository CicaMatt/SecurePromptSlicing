#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int redirect_invalid_url(const char *url) {
    const char *domain = "example.com";
    if (strstr(url, domain) != NULL) {
        return MHD_NO;
    } else {
        return MHD_YES;
    }
}

void send_response(struct MHD_Connection *connection, int status_code, const char *message) {
    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(message), (void *) message, MHD_RESPMEM_PERSISTENT);
    MHD_queue_response(connection, status_code, response);
    MHD_destroy_response(response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/redirect/") == url) {
        const char *target_url = url + strlen("/redirect/");
        if (!redirect_invalid_url(target_url)) {
            char redirect_message[] = "<html><head><title>Redirect</title></head><body>Redirecting...</body></html>";
            MHD_add_response_header(MHD_create_response_from_buffer(strlen(redirect_message), (void *) redirect_message, MHD_RESPMEM_PERSISTENT),
                                    "Location", target_url);
            send_response(connection, 302, redirect_message);
        } else {
            const char *error_message = "<html><head><title>Error</title></head><body>Invalid URL</body></html>";
            send_response(connection, 400, error_message);
        }
    } else {
        const char *not_found_message = "<html><head><title>Not Found</title></head><body>The requested URL was not found on this server.</body></html>";
        send_response(connection, 404, not_found_message);
    }

    return MHD_YES;
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