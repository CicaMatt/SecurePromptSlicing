#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct MHD_Daemon *daemon;

char* get_name_from_payload(const char *payload) {
    const char *name_start = strstr(payload, "name=");
    if (name_start == NULL) return NULL;
    name_start += 5; // length of "name="
    char *name_end = strchr(name_start, '&');
    int len = (name_end ? name_end - name_start : strlen(name_start));
    char *name = malloc(len + 1);
    strncpy(name, name_start, len);
    name[len] = '\0';
    return name;
}

int handle_api(void *cls, struct MHD_Connection *connection,
               const char *url, const char *method,
               const char *version, const char *upload_data,
               size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0) return MHD_NO;
    
    const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!query) return MHD_NO;

    char *name = get_name_from_payload(query);
    if (!name) {
        const char *error_msg = "Invalid payload";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error_msg), (void*)error_msg, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        return ret;
    }

    char *response_body = malloc(100 + strlen(name));
    snprintf(response_body, 100 + strlen(name), "{\"name\": \"%s\"}", name);
    free(name);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_body), (void*)response_body, MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_api, NULL, MHD_OPTION_END);
    if (daemon == NULL) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}