#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8888
#define DB_HOST "localhost"
#define DB_USER "user"
#define DB_PASS "password"
#define DB_NAME "weather_db"

struct connection_info_struct {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

void free_connection_info(struct connection_info_struct *info) {
    if (info->latitude)
        free(info->latitude);
    if (info->longitude)
        free(info->longitude);
    if (info->year)
        free(info->year);
    if (info->month)
        free(info->month);
    if (info->day)
        free(info->day);
    if (info->grib_file)
        free(info->grib_file);

    free(info);
}

int parse_arguments(const char *url, struct connection_info_struct **out) {
    const char *latitude = strstr(url, "latitude=");
    const char *longitude = strstr(url, "longitude=");
    const char *year = strstr(url, "year=");
    const char *month = strstr(url, "month=");
    const char *day = strstr(url, "day=");
    const char *grib_file = strstr(url, "grib_file=");

    if (!latitude || !longitude || !year || !month || !day || !grib_file) {
        return MHD_NO;
    }

    latitude += strlen("latitude=");
    longitude += strlen("longitude=");
    year += strlen("year=");
    month += strlen("month=");
    day += strlen("day=");
    grib_file += strlen("grib_file=");

    const char *next_param = strchr(latitude, '&');
    size_t lat_len = next_param ? (size_t)(next_param - latitude) : strlen(latitude);
    next_param = strchr(longitude, '&');
    size_t lon_len = next_param ? (size_t)(next_param - longitude) : strlen(longitude);
    next_param = strchr(year, '&');
    size_t year_len = next_param ? (size_t)(next_param - year) : strlen(year);
    next_param = strchr(month, '&');
    size_t month_len = next_param ? (size_t)(next_param - month) : strlen(month);
    next_param = strchr(day, '&');
    size_t day_len = next_param ? (size_t)(next_param - day) : strlen(day);
    next_param = strchr(grib_file, '&');
    size_t grib_len = next_param ? (size_t)(next_param - grib_file) : strlen(grib_file);

    struct connection_info_struct *info = malloc(sizeof(struct connection_info_struct));
    info->latitude = strndup(latitude, lat_len);
    info->longitude = strndup(longitude, lon_len);
    info->year = strndup(year, year_len);
    info->month = strndup(month, month_len);
    info->day = strndup(day, day_len);
    info->grib_file = strndup(grib_file, grib_len);

    *out = info;
    return MHD_YES;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct connection_info_struct *info;
    int result = parse_arguments(url, &info);
    if (!result)
        return MHD_NO;

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        free_connection_info(info);
        return MHD_NO;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             info->latitude, info->longitude, info->year, info->month, info->day, info->grib_file);

    if (mysql_query(conn, query)) {
        mysql_close(conn);
        free_connection_info(info);
        return MHD_NO;
    }

    MYSQL_RES *res = mysql_store_result(conn);
    MYSQL_ROW row = mysql_fetch_row(res);

    char response[128];
    snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row ? row[0] : "null");

    mysql_free_result(res);
    mysql_close(conn);
    free_connection_info(info);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                          (void *)response,
                                                                          MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}