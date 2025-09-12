#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct Payload {
    char *name;
};

void free_payload(struct Payload *payload) {
    if (payload) {
        free(payload->name);
        free(payload);
    }
}

struct Payload* parse_payload(const char *url) {
    struct Payload *payload = malloc(sizeof(struct Payload));
    payload->name = NULL;

    const char *query = strchr(url, '?');
    if (query) {
        query++; // Move past the '?'
        const char *name_prefix = "payload=";
        if (strncmp(query, name_prefix, strlen(name_prefix)) == 0) {
            payload->name = strdup(query + strlen(name_prefix));
        }
    }

    return payload;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    struct Payload *payload = parse_payload(url);
    if (!payload || !payload->name)
        return MHD_NO;

    const char *response_format = "{\"name\": \"%s\"}";
    int response_length = snprintf(NULL, 0, response_format, payload->name);
    char *response = malloc(response_length + 1);
    snprintf(response, response_length + 1, response_format, payload->name);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
        strlen(response), (void*)response, MHD_RESPMEM_MUST_FREE
    );

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    free_payload(payload);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}