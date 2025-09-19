#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <microhttpd.h>

#define PORT 8888

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    const char *name = NULL;

    if (*con_cls == NULL) {
        aptr = 0;
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (aptr < *upload_data_size) {
        name = strstr(upload_data, "name=");
        if (name != NULL) {
            name += strlen("name=");
            char *end = strchr((char *)name, '&');
            if (end != NULL)
                *end = '\0';
        }
    }

    aptr += *upload_data_size;

    struct MHD_Response *response;
    const char *response_message;

    if (name != NULL && strlen(name) > 0) {
        response_message = name;
    } else {
        response_message = "Name not found";
    }

    response = MHD_create_response_from_buffer(strlen(response_message),
                                               (void *)strdup(response_message),
                                               MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}