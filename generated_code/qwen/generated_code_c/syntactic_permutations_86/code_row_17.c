#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888
#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "weather_db"

struct RequestData {
    double latitude;
    double longitude;
    int year;
    int month;
    int day;
    char grib_file[256];
};

int handle_request(void *cls, struct MHD_Connection *connection,
                  const char *url, const char *method,
                  const char *version, const char *upload_data,
                  size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    struct RequestData *req_data = malloc(sizeof(struct RequestData));
    if (!req_data)
        return MHD_NO;

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    req_data->latitude = query_string ? atof(query_string) : 0.0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    req_data->longitude = query_string ? atof(query_string) : 0.0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    req_data->year = query_string ? atoi(query_string) : 0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    req_data->month = query_string ? atoi(query_string) : 0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    req_data->day = query_string ? atoi(query_string) : 0;
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    if (query_string)
        strncpy(req_data->grib_file, query_string, sizeof(req_data->grib_file) - 1);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        free(req_data);
        return MHD_NO;
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND YEAR(date)=%d AND MONTH(date)=%d AND DAY(date)=%d AND grib_file='%s'",
             req_data->latitude, req_data->longitude, req_data->year, req_data->month, req_data->day, req_data->grib_file);

    int ret = mysql_query(conn, query);
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    char response[128] = "Temperature not found";

    if (ret == 0 && result) {
        row = mysql_fetch_row(result);
        if (row && row[0])
            snprintf(response, sizeof(response), "Maximum Temperature: %s", row[0]);
        mysql_free_result(result);
    }

    mysql_close(conn);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), response, MHD_RESPMEM_PERSISTENT);
    int mhd_ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    free(req_data);

    return mhd_ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}