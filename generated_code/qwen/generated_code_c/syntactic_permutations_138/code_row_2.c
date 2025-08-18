#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888

MYSQL *conn;
int initDB() {
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    return 0;
}

void closeDB() {
    mysql_close(conn);
}

int checkModerator(const char *username) {
    int is_moderator = 0;
    char query[256];
    snprintf(query, sizeof(query), "SELECT is_moderator FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row != NULL && row[0] != NULL) {
        is_moderator = atoi(row[0]);
    }

    mysql_free_result(result);
    return is_moderator;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *username = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "username");
    if (!username)
        return MHD_NO;

    int is_moderator = checkModerator(username);
    const char *response = (is_moderator == 1) ? "true" : "false";

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    if (initDB() != 0) {
        fprintf(stderr, "Failed to connect to the database.\n");
        return EXIT_FAILURE;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                   &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        closeDB();
        fprintf(stderr, "Failed to start the server.\n");
        return EXIT_FAILURE;
    }

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    closeDB();
    return EXIT_SUCCESS;
}