#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *username;
    char *message;
};

void insert_user_message_in_db(const char *username, const char *message) {
    // Dummy function to simulate database insertion
    printf("Inserting into DB: User=%s, Message=%s\n", username, message);
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct ConnectionInfoStruct *con_info = (struct ConnectionInfoStruct *)cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct ConnectionInfoStruct));
        if (NULL == con_info)
            return MHD_NO;
        con_info->username = NULL;
        con_info->message = NULL;
        *con_cls = con_info;
        return MHD_YES;
    }

    if (0 != strcmp(method, "POST"))
        return MHD_NO;

    if (&aptr != *con_cls) {
        /* do not respond on first call */
        aptr = 1;
        return MHD_YES;
    }
    *con_cls = NULL;

    const char* username = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "username");
    const char* message = MHD_lookup_connection_value(connection, MHD_POSTDATA_KIND, "message");

    if (username && message) {
        con_info->username = strdup(username);
        con_info->message = strdup(message);

        insert_user_message_in_db(con_info->username, con_info->message);

        free(con_info->username);
        free(con_info->message);
    }

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(0, NULL, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, 302, response);
    MHD_add_response_header(response, "Location", "/");
    MHD_destroy_response(response);

    free(con_info);

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