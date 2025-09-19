#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

struct Payload {
    char *name;
};

void free_payload(struct Payload *payload) {
    if (payload) {
        free(payload->name);
        free(payload);
    }
}

int handle_request(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strncmp(url, "/api", 4) != 0)
        return MHD_NO;

    struct Payload *payload = malloc(sizeof(struct Payload));
    if (!payload)
        return MHD_NO;

    payload->name = NULL;
    const char *query_string = MHD_lookup_connection_value(connection,
                                                           MHD_GET_ARGUMENT_KIND,
                                                           "payload");
    if (query_string) {
        payload->name = strdup(query_string);
    }

    *con_cls = payload;

    return MHD_YES;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct Payload *payload = (struct Payload *)*con_cls;
    free_payload(payload);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        return handle_request(cls, connection, url, method, version,
                              upload_data, upload_data_size, con_cls);
    }

    struct Payload *payload = (struct Payload *)*con_cls;
    const char *response = payload->name ? payload->name : "";

    int ret;
    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                   (void *)response,
                                                   MHD_RESPMEM_MUST_COPY);
    if (!mhd_response) {
        return MHD_NO;
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              8080,
                              NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_NOTIFY_COMPLETED, request_completed,
                              NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}