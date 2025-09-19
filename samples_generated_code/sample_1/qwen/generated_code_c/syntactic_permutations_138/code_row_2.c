#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888

MYSQL *conn;
int initDatabase() {
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    return 0;
}

void closeDatabase() {
    mysql_close(conn);
}

int checkUser(const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 0;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    int exists = (mysql_num_rows(result) > 0);
    mysql_free_result(result);

    return exists;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *query = strchr(url, '?');
    if (!query) return MHD_NO;
    query++;

    const char *usernameParam = strstr(query, "username=");
    if (!usernameParam) return MHD_NO;
    usernameParam += strlen("username=");

    char username[100];
    strncpy(username, usernameParam, sizeof(username) - 1);
    username[sizeof(username) - 1] = '\0';

    int exists = checkUser(username);

    const char *response = exists ? "User exists" : "User does not exist";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void*)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    if (initDatabase()) {
        fprintf(stderr, "Failed to connect to database\n");
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon) {
        fprintf(stderr, "Failed to start server\n");
        closeDatabase();
        return 1;
    }

    printf("Server running on port %d...\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);
    closeDatabase();

    return 0;
}