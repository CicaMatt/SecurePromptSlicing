#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct Payload {
    char *name;
};

void parse_payload(const char *query_string, struct Payload *payload) {
    if (query_string != NULL) {
        const char *param = strstr(query_string, "payload=");
        if (param != NULL) {
            param += strlen("payload=");
            size_t len = strcspn(param, "&");
            payload->name = strndup(param, len);
        }
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    struct Payload payload = { NULL };
    parse_payload(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload"), &payload);

    const char *response;
    int response_size;
    if (payload.name) {
        response_size = asprintf((char **)&response, "{\"name\": \"%s\"}", payload.name);
    } else {
        response = "{\"error\": \"No payload provided\"}";
        response_size = strlen(response);
    }

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void *)response, MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);

    free(payload.name);
    MHD_destroy_response(mhd_response);

    return ret;
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