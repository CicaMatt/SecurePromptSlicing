#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct connection_info_struct {
    char *payload;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {

    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    struct connection_info_struct *con_info = cls;
    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;

        memset(con_info, 0, sizeof(struct connection_info_struct));
        *con_cls = con_info;

        return MHD_YES;
    }

    if (!strcmp(url, "/api")) {
        char name[256] = {0};
        const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
        if (query_string) {
            snprintf(name, sizeof(name), "{\"name\":\"%s\"}", query_string);
        } else {
            strcpy(name, "{}");
        }

        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(strlen(name),
                                                   (void *) name,
                                                   MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }

    return MHD_NO;
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