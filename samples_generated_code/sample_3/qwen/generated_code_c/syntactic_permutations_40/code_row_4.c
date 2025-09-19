#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "microhttpd.h"

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn_last_four;
};

void free_session_data(void *cls, enum MHD_ValueKind kind, const char *key, const char *value) {
    struct SessionData *data = (struct SessionData *) value;
    if (data) {
        free(data->username);
        free(data->email);
        free(data->ssn_last_four);
        free(data);
    }
}

int info(struct MHD_Connection *connection, void **con_cls) {
    struct MHD_Response *response;
    const char *session_id = MHD_lookup_connection_value(connection, MHD_COOKIE_KIND, "session");
    if (!session_id) {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    struct SessionData *data = (struct SessionData *) MHD_get_connection_value(connection, MHD_COOKIE_KIND, session_id);
    if (!data) {
        response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_UNAUTHORIZED, response);
    }

    char *content;
    asprintf(&content, "Username: %s<br>Email: %s<br>SSN Last 4: %s", data->username, data->email, data->ssn_last_four);

    response = MHD_create_response_from_buffer(strlen(content), (void *) content, MHD_RESPMEM_MUST_FREE);
    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/info") == 0) {
        return info(connection, con_cls);
    }
    struct MHD_Response *response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}