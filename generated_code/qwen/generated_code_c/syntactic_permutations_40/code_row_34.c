#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct SessionData {
    char *username;
    char *email;
    char *ssn;
};

void free_session_data(void *cls, enum MHD_RequestTerminationCode toe, void **con_cls) {
    struct SessionData *data = (struct SessionData *)*con_cls;
    if (NULL != data) {
        free(data->username);
        free(data->email);
        free(data->ssn);
        free(data);
        *con_cls = NULL;
    }
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (NULL == *con_cls) {
        struct SessionData *data = malloc(sizeof(struct SessionData));
        data->username = strdup("john_doe");
        data->email = strdup("john.doe@example.com");
        data->ssn = strdup("123-45-6789");
        *con_cls = data;
        MHD_add_response_header(connection, "Content-Type", "text/html");
        MHD_queue_connection_cleanup_handler(connection, MHD_REQUEST_TERMINATED_CLEANUP, free_session_data, con_cls);
    }

    if (0 != strcmp(method, "GET"))
        return MHD_NO;

    if (0 == strcmp(url, "/info")) {
        struct SessionData *data = (struct SessionData *)*con_cls;
        char response[256];
        snprintf(response, sizeof(response), "<html><body>SSN: %s</body></html>", data->ssn);
        int ret;
        struct MHD_Response *mhd_response;
        mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                       (void *)response,
                                                       MHD_RESPMEM_MUST_COPY);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);
        return ret;
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}