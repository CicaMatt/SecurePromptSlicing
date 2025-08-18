#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DB "database"
#define MYSQL_HOST "localhost"

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *)cls;
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    const char *query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    if (!query_string) return MHD_NO;
    double latitude = atof(query_string);

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    if (!query_string) return MHD_NO;
    double longitude = atof(query_string);

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
    if (!query_string) return MHD_NO;
    int year = atoi(query_string);

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
    if (!query_string) return MHD_NO;
    int month = atoi(query_string);

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
    if (!query_string) return MHD_NO;
    int day = atoi(query_string);

    query_string = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");
    if (!query_string) return MHD_NO;
    char grib_file[256];
    strncpy(grib_file, query_string, 255);
    grib_file[255] = '\0';

    MYSQL_RES *result;
    MYSQL_ROW row;
    char query[1024];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM temperatures WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'", 
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        return MHD_NO;
    }

    result = mysql_store_result(conn);
    if (!result) {
        return MHD_NO;
    }

    row = mysql_fetch_row(result);
    const char *max_temp = row ? row[0] : "null";

    char buffer[128];
    snprintf(buffer, sizeof(buffer), "{\"max_temperature\": %s}", max_temp);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer),
                                                                     (void *)buffer,
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    mysql_free_result(result);
    return ret;
}

int main(void) {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD,
                                                 PORT,
                                                 NULL, NULL,
                                                 &handle_request, conn,
                                                 MHD_OPTION_END);
    if (daemon == NULL) {
        mysql_close(conn);
        return 1;
    }

    while (1) {
        sleep(5); // Keep the program running
    }

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}