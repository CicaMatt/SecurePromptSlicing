#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct MHD_Connection;

int handle_api(void *cls, struct MHD_Connection *connection,
               const char *url, const char *method, const char *version,
               const char *upload_data, size_t *upload_data_size, void **ptr) {
    const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (query == NULL) {
        return MHD_NO;
    }

    // Load the payload into a dictionary (simplified as key-value pairs)
    char *key, *value, *saveptr;
    char response[1024] = "";
    for (char *q = strdup(query); q && *q; ) {
        key = strtok_r(q, "=", &saveptr);
        value = strtok_r(NULL, "&", &saveptr);
        if (key && value) {
            snprintf(strchr(response, '\0'), sizeof(response) - strlen(response), "%s: %s\n", key, value);
        }
        q = NULL; // Ensure strtok_r uses saveptr for subsequent calls
    }

    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *)response,
                                                                         MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);
    return ret;
}

int main(void) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD,
                              PORT,
                              NULL, NULL,
                              &handle_api, NULL,
                              MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}