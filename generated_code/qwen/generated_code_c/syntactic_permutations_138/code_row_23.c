#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8080

MYSQL *conn;

int check_moderator(const char *username) {
    int is_moderator = 0;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[256];

    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    result = mysql_store_result(conn);

    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    row = mysql_fetch_row(result);
    if (row != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(result);
    return is_moderator;
}

int handler(void *cls, struct MHD_Connection *connection,
            const char *url, const char *method,
            const char *version, const char *upload_data,
            size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *username = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "username");
    if (!username)
        return MHD_NO;

    int is_moderator = check_moderator(username);
    if (is_moderator < 0) {
        return MHD_NO;
    }

    char response[64];
    snprintf(response, sizeof(response), "{\"is_moderator\": %d}", is_moderator);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void*)response,
                                                                         MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main() {
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                &handler, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        return 1;
    }

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}