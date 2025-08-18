#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8080

MYSQL *conn;

int check_if_moderator(const char *username) {
    MYSQL_RES *result;
    MYSQL_ROW row;
    int is_moderator = 0;
    
    char query[128];
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
    if (row != NULL && strcmp(row[0], "1") == 0) {
        is_moderator = 1;
    }
    
    mysql_free_result(result);
    return is_moderator;
}

int handle_request(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/checkmoderator") != 0)
        return MHD_NO;

    struct MHD_Response *response;
    int ret;
    const char *username = "testuser"; // Example username
    int is_moderator = check_if_moderator(username);

    char response_message[64];
    snprintf(response_message, sizeof(response_message), "{\"is_moderator\": %d}", is_moderator);
    
    response = MHD_create_response_from_buffer(strlen(response_message),
                                                (void*)response_message,
                                                MHD_RESPMEM_MUST_COPY);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (daemon == NULL)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}