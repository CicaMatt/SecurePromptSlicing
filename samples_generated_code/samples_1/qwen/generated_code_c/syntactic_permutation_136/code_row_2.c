#include <stdio.h>
#include <string.h>
#include <microhttpd.h>

#define PORT 8888
#define USERNAME "admin"
#define PASSWORD "password"

int check_mod(struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, MHD_HTTP_METHOD_GET) != 0)
        return MHD_NO;

    const char *username = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "username");
    const char *password = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "password");

    if (username && password && strcmp(username, USERNAME) == 0 && strcmp(password, PASSWORD) == 0) {
        return MHD_queue_response(connection, MHD_HTTP_OK, MHD_create_response_from_buffer(strlen("true"), (void *)"true", MHD_RESPMEM_PERSISTENT));
    }

    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &check_mod, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}