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

struct connection_info_struct {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    struct connection_info_struct *con_info = malloc(sizeof(struct connection_info_struct));
    if (!con_info)
        return MHD_NO;

    con_info->latitude = NULL;
    con_info->longitude = NULL;
    con_info->year = NULL;
    con_info->month = NULL;
    con_info->day = NULL;
    con_info->grib_file = NULL;

    *con_cls = con_info;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *value;
    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    if (!value) {
        free(con_info);
        return MHD_NO;
    }
    con_info->latitude = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    if (!value) {
        free(con_info->latitude);
        free(con_info);
        return MHD_NO;
    }
    con_info->longitude = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    if (!value) {
        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info);
        return MHD_NO;
    }
    con_info->year = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    if (!value) {
        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info->year);
        free(con_info);
        return MHD_NO;
    }
    con_info->month = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    if (!value) {
        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info->year);
        free(con_info->month);
        free(con_info);
        return MHD_NO;
    }
    con_info->day = strdup(value);

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    if (!value) {
        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info->year);
        free(con_info->month);
        free(con_info->day);
        free(con_info);
        return MHD_NO;
    }
    con_info->grib_file = strdup(value);

    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info->year);
        free(con_info->month);
        free(con_info->day);
        free(con_info->grib_file);
        free(con_info);
        mysql_close(conn);
        return MHD_NO;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s "
             "AND year = %s AND month = %s AND day = %s AND grib_file = '%s'",
             con_info->latitude, con_info->longitude, con_info->year, con_info->month, con_info->day, con_info->grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info->year);
        free(con_info->month);
        free(con_info->day);
        free(con_info->grib_file);
        free(con_info);
        mysql_close(conn);
        return MHD_NO;
    }

    res = mysql_use_result(conn);

    const char *response = "Not Found";
    if ((row = mysql_fetch_row(res))) {
        response = row[0];
    }

    mysql_free_result(res);
    mysql_close(conn);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), (void *) response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

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
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}