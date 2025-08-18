#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888

struct ConnectionInfo {
    MYSQL *conn;
};

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    struct ConnectionInfo *info = cls;
    MYSQL_RES *result;
    MYSQL_ROW row;

    if (strcmp(url, "/check_user") != 0)
        return MHD_NO;

    mysql_query(info->conn, "SELECT username FROM users WHERE id=1");
    result = mysql_store_result(info->conn);
    row = mysql_fetch_row(result);

    const char *response = row ? row[0] : "User not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    mysql_free_result(result);
    return ret;
}

int main() {
    struct ConnectionInfo info;
    info.conn = mysql_init(NULL);
    if (!mysql_real_connect(info.conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(info.conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                &answer_to_connection, (void *) &info, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }
    getchar();
    mysql_close(info.conn);
    MHD_stop_daemon(daemon);
    return 0;
}