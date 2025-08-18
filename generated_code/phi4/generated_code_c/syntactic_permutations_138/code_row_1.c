#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <libmicrohttpd.h>
#include <mysql/mysql.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/check_moderator") == 0) {
        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "username", "password",
                                "database_name", 3306, NULL, 0)) {
            struct MHD_Response *response;
            const char *message = "<html><body>Error connecting to database</body></html>";
            response = MHD_create_response_from_buffer(strlen(message), (void *) message,
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
            mysql_close(conn);
            return ret;
        }

        if (mysql_query(conn, "SELECT is_moderator FROM users WHERE username='some_user'")) {
            struct MHD_Response *response;
            const char *message = "<html><body>Error executing query</body></html>";
            response = MHD_create_response_from_buffer(strlen(message), (void *) message,
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
            mysql_close(conn);
            return ret;
        }

        res = mysql_store_result(conn);
        if (!res) {
            struct MHD_Response *response;
            const char *message = "<html><body>Error retrieving query result</body></html>";
            response = MHD_create_response_from_buffer(strlen(message), (void *) message,
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
            mysql_close(conn);
            return ret;
        }

        if ((row = mysql_fetch_row(res))) {
            const char *result = row[0] ? "true" : "false";
            struct MHD_Response *response;
            char message[128];
            snprintf(message, sizeof(message), "<html><body>%s</body></html>", result);
            response = MHD_create_response_from_buffer(strlen(message), (void *) message,
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
        } else {
            struct MHD_Response *response;
            const char *message = "<html><body>User not found</body></html>";
            response = MHD_create_response_from_buffer(strlen(message), (void *) message,
                                                       MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
            MHD_destroy_response(response);
        }
        
        mysql_free_result(res);
        mysql_close(conn);

    } else {
        struct MHD_Response *response;
        const char *message = "<html><body>Not Found</body></html>";
        response = MHD_create_response_from_buffer(strlen(message), (void *) message,
                                                   MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
    }
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar(); // Wait for input to close the server

    MHD_stop_daemon(daemon);
    return 0;
}