#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888

MYSQL *conn;
int init_database() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    return 0;
}

void close_database() {
    mysql_close(conn);
}

int check_user(const char *user) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s'", user);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    int found = (mysql_num_rows(result) > 0);
    mysql_free_result(result);

    return found;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *user = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "user");
    int user_exists = check_user(user);

    const char *response = user_exists ? "User found" : "User not found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    if (init_database()) {
        fprintf(stderr, "Failed to initialize database\n");
        return 1;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT,
                                                  NULL, NULL, &answer_to_connection,
                                                  NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    close_database();

    return 0;
}