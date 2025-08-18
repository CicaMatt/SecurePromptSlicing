#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct Payload {
    char *name;
};

struct ConnectionInfoStruct {
    struct Payload payload;
    int status_code;
};

const char* get_value_from_payload(const char *key, const char *payload) {
    if (strstr(payload, key)) {
        char *start = strstr(payload, key) + strlen(key) + 1;
        char *end = strchr(start, '&');
        size_t length = end ? (size_t)(end - start) : strlen(start);
        char *value = strndup(start, length);
        return value;
    }
    return NULL;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *cis;

    if (NULL == *con_cls) {
        cis = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == cis)
            return MHD_NO;
        cis->payload.name = NULL;
        *con_cls = cis;

        return MHD_YES;
    }

    cis = *con_cls;

    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (query_string) {
        cis->payload.name = get_value_from_payload("name", query_string);
    }

    const char *response;
    if (cis->payload.name) {
        response = cis->payload.name;
    } else {
        response = "Name not found";
    }

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *)response,
                                                                         MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free(cis->payload.name);
    free(cis);
    *con_cls = NULL;

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