#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libmicrohttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (0 != strcmp(method, "GET")) return MHD_NO;
    
    if (strcmp(url, "/api/temperature_for_location") == 0) {
        struct MHD_PostProcessor *pp = NULL;
        const char* latitude = getenv("HTTP_LATITUDE");
        const char* longitude = getenv("HTTP_LONGITUDE");
        const char* year = getenv("HTTP_YEAR");
        const char* month = getenv("HTTP_MONTH");
        const char* day = getenv("HTTP_DAY");
        const char* grib_file = getenv("HTTP_GRIB_FILE");

        if (!latitude || !longitude || !year || !month || !day || !grib_file) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(0, "", MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
            MHD_destroy_response(response);
            return ret;
        }

        char query[256];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperatures WHERE latitude='%s' AND longitude='%s' "
                 "AND year=%s AND month=%s AND day=%s AND grib_file='%s'", 
                 latitude, longitude, year, month, day, grib_file);

        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        
        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(mysql_error(conn)),
                                                       mysql_error(conn), MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
            mysql_close(conn);
            return ret;
        }

        if (mysql_query(conn, query)) {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(strlen(mysql_error(conn)),
                                                       mysql_error(conn), MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
            mysql_close(conn);
            return ret;
        }

        res = mysql_store_result(conn);

        if ((row = mysql_fetch_row(res))) {
            struct MHD_Response *response;
            char buffer[256];
            snprintf(buffer, sizeof(buffer), "Maximum Temperature: %s", row[0]);
            response = MHD_create_response_from_buffer(strlen(buffer), buffer, MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);
        } else {
            struct MHD_Response *response;
            response = MHD_create_response_from_buffer(0, "No data found", MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
            MHD_destroy_response(response);
        }

        mysql_free_result(res);
        mysql_close(conn);

    } else {
        struct MHD_Response *response;
        response = MHD_create_response_from_buffer(0, "Not Found", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return ret;
    }
    
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                              PORT, NULL, NULL, &answer_to_connection, 
                              NULL, MHD_OPTION_END);

    if (NULL == daemon) return 1;
    
    printf("Server running on port %d\n", PORT);
    getchar();
    int ret = MHD_stop_daemon(daemon);
    return ret;
}
