#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                              const char *url, const char *method,
                              const char *version, const char *upload_data,
                              size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct ConnectionInfoStruct *con_info = *con_cls;
    if (NULL == con_info) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->payload = NULL;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (0 != strcmp(url, "/api"))
        return MHD_NO;

    const char *value = strchr(url, '?');
    if (value) {
        value++;
        char *name = strstr(value, "payload=");
        if (name) {
            name += 8; // Move pointer to the start of the payload value
            char *end = strchr(name, '&');
            if (!end)
                end = (char *)name + strlen(name);
            con_info->payload = strndup(name, end - name);
        }
    }

    int ret;
    struct MHD_Response *response;
    if (con_info->payload) {
        response = MHD_create_response_from_buffer(strlen(con_info->payload),
                                                   (void*)con_info->payload,
                                                   MHD_RESPMEM_MUST_FREE);
    } else {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    }
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // Wait for key press

    MHD_stop_daemon(daemon);
    return 0;
}