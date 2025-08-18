#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct PayloadData {
    char* name;
};

void parse_payload(const char* query_string, struct PayloadData* data) {
    if (query_string != NULL) {
        const char* key = "payload=";
        const char* payload_start = strstr(query_string, key);
        if (payload_start != NULL) {
            payload_start += strlen(key);
            const char* ampersand = strchr(payload_start, '&');
            size_t payload_length = ampersand ? (size_t)(ampersand - payload_start) : strlen(payload_start);
            char payload[1024];
            strncpy(payload, payload_start, payload_length);
            payload[payload_length] = '\0';

            const char* name_key = "name=";
            const char* name_start = strstr(payload, name_key);
            if (name_start != NULL) {
                name_start += strlen(name_key);
                const char* end_of_name = strchr(name_start, '&');
                size_t name_length = end_of_name ? (size_t)(end_of_name - name_start) : strlen(name_start);
                data->name = strndup(name_start, name_length);
            }
        }
    }
}

int answer_to_connection(void* cls, struct MHD_Connection* connection,
                         const char* url, const char* method,
                         const char* version, const char* upload_data,
                         size_t* upload_data_size, void** con_cls) {
    if (strcmp(url, "/api") != 0)
        return MHD_NO;

    if (*con_cls == NULL) {
        struct PayloadData* data = malloc(sizeof(struct PayloadData));
        *con_cls = data;
        return MHD_YES;
    }

    struct PayloadData* data = (struct PayloadData*)*con_cls;

    const char* query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "payload");
    parse_payload(query_string, data);

    if (data->name == NULL)
        return MHD_NO;

    int ret;
    struct MHD_Response* response = MHD_create_response_from_buffer(strlen(data->name), (void*)data->name, MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(data->name);
    free(*con_cls);
    *con_cls = NULL;

    return ret;
}

int main() {
    struct MHD_Daemon* daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}