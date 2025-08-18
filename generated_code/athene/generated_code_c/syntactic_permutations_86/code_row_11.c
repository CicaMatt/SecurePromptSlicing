#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "database"
#define MYSQL_HOST "localhost"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *)cls;
    char buffer[1024];
    int ret_code;

    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct MHD_GETArgumentsIterator iter;
    const char *key, *value;
    double latitude, longitude;
    int year, month, day;
    char grib_file[256];
    memset(grib_file, 0, sizeof(grib_file));

    ret_code = MHD_get_argument_iterator(connection, &iter);
    while (MHD_YES == MHD_get_next_argument(&iter, &key, &value)) {
        if (strcmp(key, "latitude") == 0)
            latitude = atof(value);
        else if (strcmp(key, "longitude") == 0)
            longitude = atof(value);
        else if (strcmp(key, "year") == 0)
            year = atoi(value);
        else if (strcmp(key, "month") == 0)
            month = atoi(value);
        else if (strcmp(key, "day") == 0)
            day = atoi(value);
        else if (strcmp(key, "grib_file") == 0)
            strncpy(grib_file, value, sizeof(grib_file) - 1);
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             latitude, longitude, year, month, day, grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;
    if (mysql_query(conn, query) == 0) {
        result = mysql_store_result(conn);
        if (result && (row = mysql_fetch_row(result))) {
            snprintf(buffer, sizeof(buffer), "{\"max_temperature\": \"%s\"}", row[0]);
        } else {
            snprintf(buffer, sizeof(buffer), "{\"max_temperature\": \"None\"}");
        }
        mysql_free_result(result);
    } else {
        snprintf(buffer, sizeof(buffer), "{\"error\": \"%s\"}", mysql_error(conn));
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(buffer),
                                                                     (void *)buffer,
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_add_response_header(response, "Content-Type", "application/json");
    ret_code = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret_code;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, MYSQL_HOST, MYSQL_USER, MYSQL_PASSWORD,
                            MYSQL_DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT,
                                                 NULL, NULL, &handle_request, conn,
                                                 MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "MHD_start_daemon failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    getchar();
    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}