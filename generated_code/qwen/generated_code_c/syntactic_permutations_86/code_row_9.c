#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

MYSQL *conn;
char *host = "localhost";
char *user = "root";
char *pass = "";
char *dbname = "weather";

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    static int aptr;
    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "q");
    if (!query_string)
        return MHD_NO;

    char latitude[20], longitude[20], year[5], month[3], day[3], grib_file[100];
    sscanf(query_string, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           latitude, longitude, year, month, day, grib_file);

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND YEAR(date)=%d AND MONTH(date)=%d AND DAY(date)=%d AND grib_file='%s'",
             atof(latitude), atof(longitude), atoi(year), atoi(month), atoi(day), grib_file);

    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);
    const char *response = row ? row[0] : "No data found";

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    mysql_free_result(result);
    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                  &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}