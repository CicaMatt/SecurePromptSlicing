#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *template = 
"<html>"
"    <head><title>Hello Page</title></head>"
"    <body>"
"        <h1>Hello, %s!</h1>"
"    </body>"
"</html>";

int send_page(struct MHD_Connection *connection, const char *page) {
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(page), (void *) page, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *username = url + strlen("/hello/");
    if (*url == '/' && strstr(url, "/hello/") == url && strlen(username) > 0) {
        char buffer[512];
        snprintf(buffer, sizeof(buffer), template, username);
        return send_page(connection, buffer);
    }

    return MHD_NO;
}

int main(int argc, char **argv) {
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