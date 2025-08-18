#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    const char *name = NULL;
    int ret;

    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    name = strstr(upload_data, "name=");
    if (name == NULL)
        return MHD_NO;

    // Move pointer to the start of the value
    name += strlen("name=");

    // Find end of the value
    const char *end = strchr(name, '&');
    if (!end) {
        end = upload_data + *upload_data_size;
    }

    size_t len = (size_t)(end - name);
    char* response = strndup(name, len);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(len, (void *)response, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
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