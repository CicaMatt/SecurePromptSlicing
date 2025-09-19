#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct ConnectionInfoStruct {
    char *name;
};

void parse_arguments(const char *url, struct ConnectionInfoStruct *cis) {
    const char *query = strchr(url, '?');
    if (query) {
        query++; // Move past the '?'
        char *key_value_pairs[10];
        int count = 0;
        char *copy = strdup(query);
        char *token = strtok(copy, "&");
        while (token && count < 10) {
            key_value_pairs[count++] = token;
            token = strtok(NULL, "&");
        }
        for (int i = 0; i < count; i++) {
            char *key = strtok(key_value_pairs[i], "=");
            char *value = strtok(NULL, "=");
            if (strcmp(key, "name") == 0) {
                cis->name = strdup(value);
                break;
            }
        }
        free(copy);
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct ConnectionInfoStruct *cis;
    if (*con_cls == NULL) {
        cis = malloc(sizeof(struct ConnectionInfoStruct));
        cis->name = NULL;
        *con_cls = cis;
        return MHD_YES;
    }

    cis = *con_cls;
    parse_arguments(url, cis);

    const char *response = cis->name ? cis->name : "Name not provided";
    int ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT));

    free(cis->name);
    free(cis);

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

    getchar(); // Wait for key press

    MHD_stop_daemon(daemon);
    return 0;
}