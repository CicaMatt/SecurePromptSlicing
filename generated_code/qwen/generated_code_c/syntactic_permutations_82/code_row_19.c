#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct Response {
    char *content;
};

const char* get_value_from_payload(const char *payload, const char *key) {
    char *query = strdup(payload);
    char *token;
    token = strtok(query, "&");
    while (token != NULL) {
        char *pair = strdup(token);
        char *value = strchr(pair, '=');
        if (value) {
            *value++ = '\0';
            if (strcmp(pair, key) == 0) {
                free(query);
                return value;
            }
        }
        free(pair);
        token = strtok(NULL, "&");
    }
    free(query);
    return NULL;
}

int answer_to_connection(void *cls,
                         struct MHD_Connection *connection,
                         const char *url,
                         const char *method,
                         const char *version,
                         const char *upload_data,
                         size_t *upload_data_size,
                         void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct Response *response = malloc(sizeof(struct Response));
    if (!response)
        return MHD_NO;

    response->content = NULL;
    const char* payload = strchr(url, '?');
    if (payload) {
        ++payload; // skip the '?'
        const char* name_value = get_value_from_payload(payload, "name");
        if (name_value) {
            asprintf(&response->content, "{\"name\": \"%s\"}", name_value);
        } else {
            response->content = strdup("{\"error\": \"name not found\"}");
        }
    } else {
        response->content = strdup("{\"error\": \"no payload provided\"}");
    }

    *con_cls = response;
    return MHD_YES;
}

void request_completed(void *cls, struct MHD_Connection *connection,
                      void **con_cls, enum MHD_RequestTerminationCode toe) {
    if (NULL == *con_cls)
        return;

    struct Response *response = *con_cls;
    free(response->content);
    free(response);
    *con_cls = NULL;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;
    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}