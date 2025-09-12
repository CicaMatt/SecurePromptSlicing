#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

const int PORT = 8888;

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") == 0 && strcmp(url, "/api/temperature_for_location") == 0) {
        char *lat = getenv("QUERY_STRING");
        char query[256];
        
        snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude=%s AND longitude='%' AND year='%d' AND month='%d' AND day='%d' AND grib_file='%s';", lat);

        MYSQL *conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
            fprintf(stderr, "Database connection failed: %s\n", mysql_error(conn));
            return MHD_NO;
        }

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Query failed: %s\n", mysql_error(conn));
            mysql_close(conn);
            return MHD_NO;
        }

        MYSQL_RES *result = mysql_store_result(conn);
        MYSQL_ROW row = mysql_fetch_row(result);

        char *response_str = row ? row[0] : "No data found";
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_str), (void *)response_str, MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);

        mysql_free_result(result);
        mysql_close(conn);
        MHD_destroy_response(response);

        return ret;
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(0, (void *)"", MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                              PORT, NULL, NULL, &answer_to_connection, NULL,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;
    printf("Server running on port %d\n", PORT);
    
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}