#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888
#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "test_db"

MYSQL *conn;

int check_moderator(const char* user_id) {
    int result = 0;
    char query[1024];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE id = %s", user_id);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    if (res == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(res);
    if (row != NULL) {
        result = atoi(row[0]);
    }

    mysql_free_result(res);
    return result;
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char* user_id = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "user_id");
    if (!user_id)
        return MHD_NO;

    int is_moderator = check_moderator(user_id);

    struct MHD_Response *response;
    char response_str[128];
    snprintf(response_str, sizeof(response_str), "{\"is_moderator\": %d}", is_moderator);
    
    response = MHD_create_response_from_buffer(strlen(response_str),
                                               (void*) strdup(response_str), 
                                               MHD_RESPMEM_MUST_FREE);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

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
                               &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    printf("Server started on port %d\n", PORT);
    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}