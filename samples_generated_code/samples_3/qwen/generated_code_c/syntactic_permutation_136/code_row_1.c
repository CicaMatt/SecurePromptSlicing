#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define USERNAME "admin"
#define PASSWORD "password"

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                        const char *url, const char *method,
                        const char *version, const char *upload_data,
                        size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/check_mod") == 0) {
        const char *username = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "username");
        const char *password = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "password");

        if (username && password && strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
            const char *response = "true";
            struct MHD_Response *mhd_response;
            mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
            MHD_destroy_response(mhd_response);
            return ret;
        }
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, 8888, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}