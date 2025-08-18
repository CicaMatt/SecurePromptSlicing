#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/check") != 0)
        return MHD_NO;

    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_query(conn, "SELECT * FROM your_table WHERE condition");
    result = mysql_store_result(conn);

    const char *response = "Data found!";
    int response_size = strlen(response);
    if (mysql_num_rows(result) == 0) {
        response = "No data found.";
        response_size = strlen(response);
    }

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(response_size, (void *)response, MHD_RESPMEM_PERSISTENT);

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    mysql_free_result(result);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "your_username", "your_password", "your_database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}