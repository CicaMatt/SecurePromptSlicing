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

    static int was_processed = 0;
    if (!was_processed) {
        was_processed = 1;
        return MHD_YES;
    }

    char *name_field = strstr(upload_data, "name=");
    if (name_field == NULL) {
        const char *response = "{\"error\": \"name field not found\"}";
        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    name_field += 5; // Move past "name="
    char *end_of_name = strchr(name_field, '&');
    if (end_of_name == NULL)
        end_of_name = name_field + strlen(name_field);

    size_t name_length = end_of_name - name_field;
    char *name_value = malloc(name_length + 1);
    strncpy(name_value, name_field, name_length);
    name_value[name_length] = '\0';

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(name_value), (void*) name_value, MHD_RESPMEM_MUST_FREE);
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

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}