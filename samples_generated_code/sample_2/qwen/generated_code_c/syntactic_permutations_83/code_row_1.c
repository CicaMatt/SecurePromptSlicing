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

    if (*upload_data_size != 0) {
        // Parse the payload to check for 'name'
        const char *name_field = strstr(upload_data, "name=");
        if (name_field != NULL) {
            name_field += strlen("name=");
            const char *end_of_name = strchr(name_field, '&');
            size_t name_length;
            if (end_of_name == NULL)
                name_length = strlen(name_field);
            else
                name_length = end_of_name - name_field;

            char *response = malloc(2048);
            snprintf(response, 2048, "Name: %.*s", (int)name_length, name_field);

            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
            MHD_destroy_response(mhd_response);
            return ret;
        }
    }

    const char *not_found_msg = "Name field not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(not_found_msg), (void *)not_found_msg, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
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

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}