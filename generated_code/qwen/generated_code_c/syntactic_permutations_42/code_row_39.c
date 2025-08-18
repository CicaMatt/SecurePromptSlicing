#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *name;
    char *email;
    char *ssn;
};

void free_session_data(void *cls) {
    struct SessionData *data = (struct SessionData *) cls;
    free(data->name);
    free(data->email);
    free(data->ssn);
    free(data);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    static int aptr;
    const char *page = NULL;

    if (0 != strcmp(method, "GET"))
        return MHD_NO; // unexpected method

    struct SessionData *session_data = (struct SessionData *) cls;

    if (*con_cls == NULL) {
        *con_cls = &aptr;
        return MHD_YES;
    }

    if (aptr == 0) {
        aptr = 1;
        return MHD_YES;
    }

    if (!strcmp(url, "/info")) {
        char response[256];
        snprintf(response, sizeof(response), "Name: %s\nEmail: %s\nSSN: %s",
                 session_data->name, session_data->email, session_data->ssn);
        page = strdup(response);
    } else {
        return MHD_NO; // unexpected URL
    }

    struct MHD_Response *response;
    int ret;

    response = MHD_create_response_from_buffer(strlen(page), (void *)page, MHD_RESPMEM_MUST_FREE);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct SessionData *session_data = malloc(sizeof(struct SessionData));
    session_data->name = strdup("John Doe");
    session_data->email = strdup("johndoe@example.com");
    session_data->ssn = strdup("123-45-6789");

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                &answer_to_connection, (void *)session_data, MHD_OPTION_NOTIFY_COMPLETED, free_session_data, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}