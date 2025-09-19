#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct MHD_Daemon *daemon;

char* get_value_from_query(const char *query, const char *key) {
    char *result = NULL;
    if (query && key) {
        size_t key_len = strlen(key);
        char *start = strstr(query, key);
        if (start) {
            start += key_len + 1; // skip over the '='
            result = strdup(start);
            char *end = strchr(result, '&');
            if (end) *end = '\0';
        }
    }
    return result;
}

int handle_api(void *cls, struct MHD_Connection *connection,
               const char *url, const char *method,
               const char *version, const char *upload_data,
               size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) return MHD_NO;

    const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "name");
    if (!query) query = "";

    char *response = get_value_from_query(query, "name");
    if (!response) response = strdup("Name not provided");

    struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                 (void *)response,
                                                                 MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, resp);
    MHD_destroy_response(resp);
    return ret;
}

int main(void) {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD,
                              PORT,
                              NULL, NULL,
                              &handle_api, NULL,
                              MHD_OPTION_END);
    if (daemon == NULL) return 1;

    getchar(); // Wait for user input to terminate the server

    MHD_stop_daemon(daemon);
    return 0;
}