#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL *conn;
char *host = "localhost";
char *user = "root";
char *pass = "password";
char *dbname = "weather_data";

int query_database(double latitude, double longitude, int year, int month, int day, const char* grib_file) {
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather WHERE latitude = %f AND longitude = %f AND YEAR(date) = %d AND MONTH(date) = %d AND DAY(date) = %d AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return MHD_NO;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row != NULL) {
        printf("Maximum Temperature: %s\n", row[0] ? row[0] : "NULL");
    } else {
        printf("No data found.\n");
    }
    mysql_free_result(res);
    return MHD_YES;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    double latitude, longitude;
    int year, month, day;
    const char* grib_file;

    latitude = atof(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude"));
    longitude = atof(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude"));
    year = atoi(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year"));
    month = atoi(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month"));
    day = atoi(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day"));
    grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

    if (!grib_file) {
        return MHD_NO;
    }

    int ret = query_database(latitude, longitude, year, month, day, grib_file);

    const char *page = "<html><body>Hello world</body></html>";
    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(page), (void*) page, MHD_RESPMEM_PERSISTENT);
    int result = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, host, user, pass, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                               &answer_to_connection, NULL, MHD_OPTION_END);

    if (daemon == NULL)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}