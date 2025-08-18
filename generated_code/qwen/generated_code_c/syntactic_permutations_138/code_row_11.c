#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

int check_moderator(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        char query[256];
        snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='test_user'");

        if (mysql_query(conn, query) == 0) {
            res = mysql_use_result(conn);
            row = mysql_fetch_row(res);

            int is_moderator = row[0] ? atoi(row[0]) : 0;
            mysql_free_result(res);
            mysql_close(conn);

            char response[256];
            snprintf(response, sizeof(response), "{\"is_moderator\": %d}", is_moderator);

            struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                                (void*)response,
                                                                                MHD_RESPMEM_MUST_COPY);
            return MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        }
    }

    mysql_close(conn);
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &check_moderator, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}