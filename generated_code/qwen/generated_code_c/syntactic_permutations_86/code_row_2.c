#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfo {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

void free_connection_info(struct ConnectionInfo *info) {
    free(info->latitude);
    free(info->longitude);
    free(info->year);
    free(info->month);
    free(info->day);
    free(info->grib_file);
}

int parse_query_string(const char *query_string, struct ConnectionInfo *info) {
    info->latitude = strdup(strchr(query_string, '=') + 1);
    const char *longitude_start = strchr(info->latitude, '&') + strlen("longitude=");
    info->longitude = strndup(longitude_start, strchr(longitude_start, '&') - longitude_start);

    const char *year_start = strchr(info->longitude, '&') + strlen("year=");
    info->year = strndup(year_start, strchr(year_start, '&') - year_start);

    const char *month_start = strchr(info->year, '&') + strlen("month=");
    info->month = strndup(month_start, strchr(month_start, '&') - month_start);

    const char *day_start = strchr(info->month, '&') + strlen("day=");
    info->day = strndup(day_start, strchr(day_start, '&') - day_start);

    const char *grib_file_start = strchr(info->day, '&') + strlen("grib_file=");
    info->grib_file = strdup(grib_file_start);

    return 0;
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    struct ConnectionInfo info;
    parse_query_string(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude"), &info);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        free_connection_info(&info);
        return MHD_NO;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperatures WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
             info.latitude, info.longitude, info.year, info.month, info.day, info.grib_file);

    if (mysql_query(conn, query)) {
        mysql_close(conn);
        free_connection_info(&info);
        return MHD_NO;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(result);

    const char *response = row[0] ? row[0] : "No data found";
    int response_size = strlen(response);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_size, (void *) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    mysql_free_result(result);
    mysql_close(conn);
    free_connection_info(&info);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}