#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct PayloadData {
    char *name;
};

void parse_query_string(const char *query, struct PayloadData *data) {
    const char *key = "payload=";
    size_t key_len = strlen(key);
    if (strncmp(query, key, key_len) == 0) {
        const char *payload_start = query + key_len;
        char payload[256];
        snprintf(payload, sizeof(payload), "%s", payload_start);

        // Assuming the payload is in JSON format: {"name": "value"}
        const char *name_key = "\"name\":\"";
        size_t name_key_len = strlen(name_key);
        const char *name_start = strstr(payload, name_key);
        if (name_start != NULL) {
            name_start += name_key_len;
            const char *name_end = strchr(name_start, '"');
            if (name_end != NULL) {
                size_t name_len = name_end - name_start;
                data->name = strndup(name_start, name_len);
            }
        }
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct PayloadData *data = malloc(sizeof(struct PayloadData));
        data->name = NULL;
        *con_cls = data;
        return MHD_YES;
    }

    struct PayloadData *data = (struct PayloadData *)*con_cls;
    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    if (query_string != NULL) {
        parse_query_string(query_string, data);
    }

    const char *response = data->name ? data->name : "Name not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    free(data->name);
    free(data);
    *con_cls = NULL;

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}