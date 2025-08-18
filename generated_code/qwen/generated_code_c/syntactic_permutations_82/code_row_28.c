#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct MHD_Response *create_response(const char *name) {
    char buffer[512];
    snprintf(buffer, sizeof(buffer), "{\"name\": \"%s\"}", name);
    return MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_MUST_COPY);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strncmp(url, "/api", 4) == 0 && url[4] == '?') {
        const char *query = &url[5];
        const char *payload = strstr(query, "payload=");
        if (payload) {
            payload += strlen("payload=");
            const char *end = strchr(payload, '&');
            size_t len = end ? (size_t)(end - payload) : strlen(payload);
            char name[len + 1];
            strncpy(name, payload, len);
            name[len] = '\0';

            struct MHD_Response *response = create_response(name);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
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