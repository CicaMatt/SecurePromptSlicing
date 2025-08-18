#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define DATABASE "weather_db"
#define USER "root"
#define PASSWORD "password"

struct ConnectionInfo {
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
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    struct ConnectionInfo *ci = malloc(sizeof(struct ConnectionInfo));
    if (!ci)
        return MHD_NO;
    *con_cls = ci;

    const char *query = MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND);
    if (query) {
        sscanf(query, "latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%255s",
               &ci->latitude, &ci->longitude, &ci->year, &ci->month, &ci->day, ci->grib_file);
    } else {
        free(ci);
        return MHD_NO;
    }

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(ci);
        mysql_close(conn);
        return MHD_NO;
    }

    char query_str[1024];
    snprintf(query_str, sizeof(query_str),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %lf AND longitude = %lf AND YEAR(date) = %d AND MONTH(date) = %d AND DAY(date) = %d AND grib_file = '%s'",
             ci->latitude, ci->longitude, ci->year, ci->month, ci->day, ci->grib_file);

    if (mysql_query(conn, query_str)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(ci);
        mysql_close(conn);
        return MHD_NO;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    char response[256] = "Temperature not found";
    if (result && (row = mysql_fetch_row(result))) {
        snprintf(response, sizeof(response), "Maximum Temperature: %s", row[0]);
    }
    mysql_free_result(result);

    int ret;
    struct MHD_Response *response_obj = MHD_create_response_from_buffer(strlen(response),
                                                                         (void *) response,
                                                                         MHD_RESPMEM_PERSISTENT);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response_obj);
    MHD_destroy_response(response_obj);

    free(ci);
    mysql_close(conn);

    return ret;
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