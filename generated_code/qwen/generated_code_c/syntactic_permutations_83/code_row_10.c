#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

const char *get_value_from_payload(const char* payload, const char* key) {
    char* token;
    char* temp = strdup(payload);
    token = strtok(temp, "&");
    while (token != NULL) {
        if (strncmp(token, key, strlen(key)) == 0) {
            free(temp);
            return strchr(token, '=') + 1;
        }
        token = strtok(NULL, "&");
    }
    free(temp);
    return NULL;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    if (*upload_data_size != 0) {
        const char* name_value = get_value_from_payload(upload_data, "name");
        if (name_value != NULL) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(name_value),
                                                      (void*)name_value,
                                                      MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
            return ret;
        }
    }

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}