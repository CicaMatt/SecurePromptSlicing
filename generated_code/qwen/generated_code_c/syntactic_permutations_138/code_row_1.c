#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888

int check_moderator(const char *user_id) {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    int is_moderator = 0;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = '%s'", user_id);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        result = mysql_store_result(conn);
        if (result == NULL) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            row = mysql_fetch_row(result);
            if (row != NULL && strcmp(row[0], "1") == 0) {
                is_moderator = 1;
            }
            mysql_free_result(result);
        }
    }

    mysql_close(conn);
    return is_moderator;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/check_moderator") != 0)
        return MHD_NO;

    const char *user_id = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "user_id");
    if (!user_id)
        return MHD_NO;

    int is_moderator = check_moderator(user_id);

    const char *response = is_moderator ? "{\"is_moderator\": true}" : "{\"is_moderator\": false}";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}