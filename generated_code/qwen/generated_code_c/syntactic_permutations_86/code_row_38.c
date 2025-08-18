#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <microhttpd.h>
#include <mysql/mysql.h>

#define PORT 8080

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strncmp(url, "/api/temperature_for_location?", 28) != 0)
        return MHD_NO;

    const char *params = url + 28;
    char latitude[50] = "", longitude[50] = "", year[50] = "",
             month[50] = "", day[50] = "", grib_file[100] = "";
    sscanf(params, "latitude=%49[^&]&longitude=%49[^&]&year=%49[^&]&month=%49[^&]&day=%49[^&]&grib_file=%99s",
           latitude, longitude, year, month, day, grib_file);

    char query[256];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM weather_data WHERE latitude='%s' AND longitude='%s' AND YEAR(date)='%s' AND MONTH(date)='%s' AND DAY(date)='%s' AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        const char *error = mysql_error(conn);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error),
                                                                         (void *) error,
                                                                         MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        const char *error = mysql_error(conn);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error),
                                                                         (void *) error,
                                                                         MHD_RESPMEM_PERSISTENT);
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    const char *temperature = row ? row[0] : "No data found";

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(temperature),
                                                                     (void *) temperature,
                                                                     MHD_RESPMEM_PERSISTENT);
    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);

    return 0;
}