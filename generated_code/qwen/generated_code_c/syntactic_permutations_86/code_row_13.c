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
char *dbname = "weather_data";

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "lat");
    double latitude = query_string ? atof(query_string) : 0.0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "lon");
    double longitude = query_string ? atof(query_string) : 0.0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    int year = query_string ? atoi(query_string) : 0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    int month = query_string ? atoi(query_string) : 0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    int day = query_string ? atoi(query_string) : 0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    char *grib_file = (char *)query_string;

    if (!grib_file || !*grib_file)
        return MHD_NO;

    MYSQL_RES *result;
    MYSQL_ROW row;

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather WHERE latitude=%.6f AND longitude=%.6f AND YEAR(date)=%d AND MONTH(date)=%d AND DAY(date)=%d AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return MHD_NO;
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    const char *response = row[0] ? row[0] : "No data found";

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                          (void *) response,
                                                                          MHD_RESPMEM_PERSISTENT);
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
                                                &handle_request, NULL,
                                                MHD_OPTION_END);
    if (NULL == daemon) {
        return 1;
    }

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}