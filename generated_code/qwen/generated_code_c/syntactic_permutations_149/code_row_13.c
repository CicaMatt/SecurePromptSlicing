#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8080

struct ConnectionInfoStruct {
    char *username;
    char *message;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                               const char *url, const char *method,
                               const char *version, const char *upload_data,
                               size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfoStruct *con_info = cls;
    int ret;
    const char *username = NULL, *message = NULL;

    if (0 == strcmp(method, "POST")) {
        if (*con_cls == NULL) {
            con_info = malloc(sizeof(struct ConnectionInfoStruct));
            if (con_info == NULL)
                return MHD_NO;
            con_info->username = NULL;
            con_info->message = NULL;
            *con_cls = con_info;
            return MHD_YES;
        }
        if (*upload_data_size != 0) {
            const char *data = upload_data;

            while (*data == ' ')
                data++;
            username = strstr(data, "username=");
            message = strstr(data, "message=");

            if (username && message) {
                username += strlen("username=");
                message += strlen("message=");
                con_info->username = strndup(username, strchr(username, '&') - username);
                con_info->message = strndup(message, strchr(message, '&') - message);
            }

            *upload_data_size = 0;
        }
    } else {
        return MHD_NO;
    }

    if (con_info->username && con_info->message) {
        char response[512];
        snprintf(response, sizeof(response), "Received message from %s: %s", con_info->username, con_info->message);
        ret = MHD_queue_response(connection, MHD_HTTP_OK,
                                  MHD_create_response_from_buffer(strlen(response),
                                                                  (void *)response,
                                                                  MHD_RESPMEM_MUST_FREE));
    } else {
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, NULL);
    }

    free(con_info->username);
    free(con_info->message);

    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}