#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct connection_info_struct {
    const char *name;
};

static int handle_api(void *cls, struct MHD_Connection *connection,
                      const char *url, const char *method,
                      const char *version, const char *upload_data,
                      size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *ci = (struct connection_info_struct *)*con_cls;
    if (NULL == ci) {
        ci = malloc(sizeof(struct connection_info_struct));
        ci->name = NULL;
        *con_cls = ci;
    }

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (query_string != NULL) {
        char *decoded_query = strdup(query_string);
        char *key = strtok(decoded_query, "=");
        char *value = strtok(NULL, "=");
        if (strcmp(key, "name") == 0 && value != NULL) {
            ci->name = value;
        }
        free(decoded_query);
    }

    struct MHD_Response *response;
    int ret;

    if (ci->name != NULL) {
        char buffer[256];
        snprintf(buffer, sizeof(buffer), "{\"name\": \"%s\"}", ci->name);
        response = MHD_create_response_from_buffer(strlen(buffer), (void *)buffer, MHD_RESPMEM_MUST_COPY);
    } else {
        const char *error_message = "{\"error\": \"Name not found in payload\"}";
        response = MHD_create_response_from_buffer(strlen(error_message), (char *)error_message, MHD_RESPMEM_PERSISTENT);
    }

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(ci);
    *con_cls = NULL;

    return ret;
}

int main(void) {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_api, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}