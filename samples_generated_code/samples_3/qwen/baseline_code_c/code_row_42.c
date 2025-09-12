#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    const char* name_field = "name=";
    size_t name_len = strlen(name_field);
    char *name_start = strstr((char*) upload_data, name_field);

    if (!name_start || *upload_data_size == 0) {
        return MHD_NO;
    }

    name_start += name_len;

    int content_length = atoi(MHD_lookup_connection_value(connection, MHD_HEADER_KIND, "Content-Length"));
    char *response_end = strchr(name_start, '&');
    int response_len = (response_end ? response_end - name_start : content_length - (name_start - upload_data));

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(response_len, (void*) name_start, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
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