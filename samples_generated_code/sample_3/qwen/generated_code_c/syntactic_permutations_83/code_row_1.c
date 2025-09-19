#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") == 0 && upload_data != NULL) {
        const char *name_field = "name=";
        size_t name_len = strlen(name_field);
        const char *data_start = strstr(upload_data, name_field);

        if (data_start != NULL) {
            data_start += name_len;
            const char *end = strchr(data_start, '&');

            if (end == NULL) {
                end = upload_data + *upload_data_size;
            }

            size_t name_length = end - data_start;

            char *response = malloc(name_length + 1);
            strncpy(response, data_start, name_length);
            response[name_length] = '\0';

            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
                    strlen(response), (void *)response, MHD_RESPMEM_MUST_FREE);

            int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
            MHD_destroy_response(mhd_response);
            return ret;
        }
    }

    const char *not_found_message = "Name field not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(
            strlen(not_found_message), (void *)not_found_message, MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}