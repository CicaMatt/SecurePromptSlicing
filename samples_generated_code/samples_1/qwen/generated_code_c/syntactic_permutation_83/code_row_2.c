#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                       const char *url, const char *method,
                       const char *version, const char *upload_data,
                       size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    static int aptr;
    struct MHD_Response *response;
    int ret;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    const char* name_value = strstr(upload_data, "name=");
    if (name_value != NULL) {
        name_value += 5; // Move past "name="
        char* end_of_name = strchr(name_value, '&');
        int length = (end_of_name == NULL) ? strlen(name_value) : (end_of_name - name_value);
        char name[length + 1];
        strncpy(name, name_value, length);
        name[length] = '\0';

        response = MHD_create_response_from_buffer(strlen(name), (void*)name, MHD_RESPMEM_MUST_FREE);
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

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}