#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *payload;
};

void free_connection_info(void *coninfo_cls) {
    struct connection_info_struct *cis = coninfo_cls;
    free(cis->payload);
    free(cis);
}

const char* get_value_from_payload(const char* payload, const char* key) {
    // Simple implementation assuming JSON-like format
    char* search_key = malloc(strlen(key) + 4); // "key":"
    strcpy(search_key, "\"");
    strcat(search_key, key);
    strcat(search_key, "\":");

    const char* start = strstr(payload, search_key);
    if (start == NULL) {
        free(search_key);
        return NULL;
    }

    start += strlen(search_key);
    const char* end = strchr(start, '"');

    size_t length = end - start;
    char* result = malloc(length + 1);
    strncpy(result, start, length);
    result[length] = '\0';

    free(search_key);
    return result;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info;
    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (con_info == NULL)
            return MHD_NO;
        con_info->payload = strdup(url);
        *con_cls = con_info;
        return MHD_YES;
    }

    con_info = *con_cls;

    const char* query = strchr(con_info->payload, '?');
    if (query == NULL) {
        free_connection_info(con_info);
        *con_cls = NULL;
        return MHD_NO;
    }
    query++; // skip '?'

    const char* payload_param = strstr(query, "payload=");
    if (payload_param == NULL) {
        free_connection_info(con_info);
        *con_cls = NULL;
        return MHD_NO;
    }
    payload_param += 8; // skip 'payload='

    const char* end_of_payload = strchr(payload_param, '&');
    size_t payload_length = end_of_payload ? (end_of_payload - payload_param) : strlen(payload_param);

    char* payload = malloc(payload_length + 1);
    strncpy(payload, payload_param, payload_length);
    payload[payload_length] = '\0';

    const char* name_value = get_value_from_payload(payload, "name");

    struct MHD_Response *response;
    int ret;

    if (name_value == NULL) {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    } else {
        response = MHD_create_response_from_buffer(strlen(name_value), (void*)name_value, MHD_RESPMEM_MUST_COPY);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        free((char*)name_value); // allocated in get_value_from_payload
    }

    free(payload);

    MHD_destroy_response(response);
    free_connection_info(con_info);
    *con_cls = NULL;

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar(); // keep server running

    MHD_stop_daemon(daemon);
    return 0;
}