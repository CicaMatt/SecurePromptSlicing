#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

struct connection_info_struct {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

int get_temperature(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info;
    const char *value;
    con_info = malloc(sizeof(struct connection_info_struct));
    if (!con_info)
        return MHD_NO;

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    if (value)
        con_info->latitude = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    if (value)
        con_info->longitude = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    if (value)
        con_info->year = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    if (value)
        con_info->month = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    if (value)
        con_info->day = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    if (value)
        con_info->grib_file = strdup(value);

    *con_cls = con_info;
    return MHD_YES;
}

int send_response(void *cls, struct MHD_Connection *connection) {
    struct connection_info_struct *con_info = cls;

    MYSQL *conn;
    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[500];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        return MHD_NO;
    }

    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND YEAR(date)=%s AND MONTH(date)=%s AND DAY(date)=%s AND grib_file='%s'",
             atof(con_info->latitude), atof(con_info->longitude),
             con_info->year, con_info->month, con_info->day,
             con_info->grib_file);

    mysql_query(conn, query);
    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    const char *response_text;
    if (row[0]) {
        response_text = row[0];
    } else {
        response_text = "No data found";
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_text), (void *) response_text, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    mysql_free_result(result);
    mysql_close(conn);

    free(con_info->latitude);
    free(con_info->longitude);
    free(con_info->year);
    free(con_info->month);
    free(con_info->day);
    free(con_info->grib_file);
    free(con_info);

    return ret;
}

int main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &get_temperature, NULL, MHD_OPTION_NOTIFY_COMPLETED,
                              send_response, NULL, MHD_OPTION_END);
    if (!daemon)
        return 1;

    printf("Server started on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}