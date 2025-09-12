#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "testdb"

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/check") == 0 && strcmp(method, "GET") == 0) {
        MYSQL_RES *result;
        MYSQL_ROW row;

        if (mysql_query(conn, "SELECT * FROM test_table WHERE condition_column = 'some_condition'")) {
            return MHD_NO;
        }

        result = mysql_store_result(conn);
        if (result == NULL) {
            return MHD_NO;
        }

        int num_fields = mysql_num_fields(result);
        row = mysql_fetch_row(result);

        char response[1024];
        snprintf(response, sizeof(response), "Check Result: %s", row ? row[0] : "No data");

        mysql_free_result(result);

        struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                             (void *)response,
                                                                             MHD_RESPMEM_MUST_COPY);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
        MHD_destroy_response(mhd_response);

        return ret;
    }

    return MHD_NO;
}

int main(int argc, char *argv[]) {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}