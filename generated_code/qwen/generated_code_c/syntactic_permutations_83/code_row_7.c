#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int post_processed = 0;
    struct MHD_Response *response;
    int ret;

    if (!post_processed) {
        post_processed = 1;
        return MHD_YES;
    }

    char name[256] = "";
    const char *content_type = MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "Content-Type");
    if (content_type && strstr(content_type, "application/x-www-form-urlencoded")) {
        const char *name_start = strstr(upload_data, "name=");
        if (name_start) {
            name_start += 5; // Move past "name="
            size_t len = strcspn(name_start, "&");
            strncpy(name, name_start, len);
            name[len] = '\0';
        }
    }

    response = MHD_create_response_from_buffer(strlen(name), (void *)name, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}