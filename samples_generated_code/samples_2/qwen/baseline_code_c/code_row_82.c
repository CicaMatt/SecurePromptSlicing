#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

int handle_request(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    struct MHD_Response *response;
    int ret;

    if (*con_cls == NULL) {
        *con_cls = malloc(sizeof(int));
        if (*con_cls == NULL)
            return MHD_NO;
        aptr = 0;
        *upload_data_size = 0;
        return MHD_YES;
    }

    if (aptr < *upload_data_size) {
        printf("Data: %.*s\n", (int)*upload_data_size, upload_data);
        int name_len = snprintf(NULL, 0, "name=");
        char *name_start = strstr(upload_data + aptr, "name=");
        if (name_start != NULL) {
            name_start += name_len;
            char *name_end = strchr(name_start, '&');
            size_t name_size = (name_end == NULL) ? strlen(name_start) : name_end - name_start;
            char name[name_size + 1];
            strncpy(name, name_start, name_size);
            name[name_size] = '\0';
            response = MHD_create_response_from_buffer(strlen(name), (void*)strdup(name), MHD_RESPMEM_MUST_FREE);
        } else {
            response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        }
    } else {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(*con_cls);
    *con_cls = NULL;

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}