#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "microhttpd.h"

#define PORT 8080
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "forum_db"

MYSQL *conn;

int check_moderator(const char* username) {
    int result = 0;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[256];

    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return result;
    }

    res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return result;
    }

    row = mysql_fetch_row(res);
    if (row != NULL && row[0] != NULL) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    return result;
}

int handle_request(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    const char* username = "test_user"; // Example user
    int is_moderator = check_moderator(username);
    char response[256];
    snprintf(response, sizeof(response), "{\"is_moderator\": %d}", is_moderator);

    struct MHD_Response *mhd_response;
    mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                   (void*)response,
                                                   MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}