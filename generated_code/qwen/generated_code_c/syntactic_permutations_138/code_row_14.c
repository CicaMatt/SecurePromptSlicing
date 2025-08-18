#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "forum"

MYSQL *conn;

int check_moderator(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    int ret;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[256];
    char user_id[] = "1"; // Example user ID

    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = %s", user_id);

    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    const char *response = row ? row[0] : "0";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    mysql_free_result(result);
    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &check_moderator, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}