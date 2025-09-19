#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct PayloadData {
    char *name;
};

int parse_query_string(const char *query, struct PayloadData *data) {
    char *key, *value, *saveptr1, *saveptr2;
    char *query_copy = strdup(query);

    for (key = strtok_r(query_copy, "&", &saveptr1); key != NULL; key = strtok_r(NULL, "&", &saveptr1)) {
        value = strchr(key, '=');
        if (value) {
            *value++ = '\0';
            if (strcmp(key, "payload") == 0) {
                char *payload_copy = strdup(value);
                for (char *token = strtok_r(payload_copy, ",", &saveptr2); token != NULL; token = strtok_r(NULL, ",", &saveptr2)) {
                    char *eq = strchr(token, '=');
                    if (eq) {
                        *eq++ = '\0';
                        if (strcmp(token, "name") == 0) {
                            data->name = strdup(eq);
                        }
                    }
                }
                free(payload_copy);
            }
        }
    }

    free(query_copy);
    return 0;
}

int handler(void *cls, struct MHD_Connection *connection,
          const char *url, const char *method,
          const char *version, const char *upload_data,
          size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api") != 0)
        return MHD_NO;

    const char *query = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (!query)
        return MHD_NO;

    struct PayloadData data = {0};
    parse_query_string(query, &data);

    const char *response = data.name ? data.name : "Name not found";
    int response_size = strlen(response);
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void *)response, MHD_RESPMEM_MUST_FREE);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    if (data.name)
        free(data.name);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handler, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}