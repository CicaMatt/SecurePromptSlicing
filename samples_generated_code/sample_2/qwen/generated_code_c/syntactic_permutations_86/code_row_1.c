#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    char lat[15], lon[15], year[5], month[3], day[3], grib_file[256];
    memset(lat, 0, sizeof(lat));
    memset(lon, 0, sizeof(lon));
    memset(year, 0, sizeof(year));
    memset(month, 0, sizeof(month));
    memset(day, 0, sizeof(day));
    memset(grib_file, 0, sizeof(grib_file));

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "lat");
    if (query_string) snprintf(lat, sizeof(lat), "%s", query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "lon");
    if (query_string) snprintf(lon, sizeof(lon), "%s", query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    if (query_string) snprintf(year, sizeof(year), "%s", query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    if (query_string) snprintf(month, sizeof(month), "%s", query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    if (query_string) snprintf(day, sizeof(day), "%s", query_string);
    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    if (query_string) snprintf(grib_file, sizeof(grib_file), "%s", query_string);

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%.6f AND longitude=%.6f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             atof(lat), atof(lon), atoi(year), atoi(month), atoi(day), grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query(conn, query)) {
        const char* error_response = "Error executing query";
        return MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR,
                                  MHD_create_response_from_buffer(strlen(error_response),
                                                                 (void*)error_response,
                                                                 MHD_RESPMEM_PERSISTENT));
    }

    result = mysql_store_result(conn);
    row = mysql_fetch_row(result);

    const char* response = row ? row[0] : "No data found";
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                         (void*)response,
                                                                         MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    mysql_free_result(result);
    MHD_destroy_response(mhd_response);

    return ret;
}

int main() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    getchar();

    mysql_close(conn);

    MHD_stop_daemon(daemon);

    return 0;
}