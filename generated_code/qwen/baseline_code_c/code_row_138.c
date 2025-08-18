#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8080
#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "database"

int check_moderator(const char *username) {
    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    row = mysql_fetch_row(result);
    int is_moderator = 0;
    if (row != NULL && row[0] != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(result);
    mysql_close(conn);

    return is_moderator;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/check_moderator") != 0)
        return MHD_NO;

    const char *username = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "username");
    if (!username)
        return MHD_NO;

    int is_moderator = check_moderator(username);

    char response[128];
    snprintf(response, sizeof(response), "{\"is_moderator\": %d}", is_moderator);
    
    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                          (void *)response,
                                                                          MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);

    MHD_destroy_response(response_obj);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}