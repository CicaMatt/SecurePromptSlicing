#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    struct MHD_PostProcessor *pp = NULL;
    pp = MHD_create_post_processor(connection, 1024, POST_iterator, NULL);
    if (NULL == pp)
        return MHD_NO;

    int ret;
    char response[1024];
    const char *lat_key = "latitude";
    const char *lon_key = "longitude";
    const char *year_key = "year";
    const char *month_key = "month";
    const char *day_key = "day";
    const char *grib_file_key = "grib_file";

    char lat[64], lon[64], year[8], month[3], day[3], grib_file[256];

    MHD_get_connection_values(connection,
                              MHD_GET_ARGUMENT_KIND, NULL, &lat_key, &lat, sizeof(lat), NULL);
    MHD_get_connection_values(connection,
                              MHD_GET_ARGUMENT_KIND, NULL, &lon_key, &lon, sizeof(lon), NULL);
    MHD_get_connection_values(connection,
                              MHD_GET_ARGUMENT_KIND, NULL, &year_key, &year, sizeof(year), NULL);
    MHD_get_connection_values(connection,
                              MHD_GET_ARGUMENT_KIND, NULL, &month_key, &month, sizeof(month), NULL);
    MHD_get_connection_values(connection,
                              MHD_GET_ARGUMENT_KIND, NULL, &day_key, &day, sizeof(day), NULL);
    MHD_get_connection_values(connection,
                              MHD_GET_ARGUMENT_KIND, NULL, &grib_file_key, &grib_file, sizeof(grib_file), NULL);

    MYSQL *mysql = mysql_init(NULL);
    if (!mysql) {
        snprintf(response, sizeof(response), "MySQL initialization failed");
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response,
                                 strlen(response));
        return ret;
    }

    if (mysql_real_connect(mysql, "localhost", "user", "password", "database",
                           0, NULL, 0) == NULL) {
        snprintf(response, sizeof(response), "MySQL connection failed: %s",
                 mysql_error(mysql));
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response,
                                 strlen(response));
        mysql_close(mysql);
        return ret;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperatures WHERE latitude='%s' AND longitude='%s' "
             "AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
             lat, lon, year, month, day, grib_file);

    if (mysql_query(mysql, query)) {
        snprintf(response, sizeof(response), "MySQL query failed: %s", mysql_error(mysql));
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response,
                                 strlen(response));
        mysql_close(mysql);
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(mysql);
    if (!result) {
        snprintf(response, sizeof(response), "MySQL result retrieval failed: %s", mysql_error(mysql));
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response,
                                 strlen(response));
        mysql_close(mysql);
        return ret;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    if (row && row[0]) {
        snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
    } else {
        snprintf(response, sizeof(response), "{\"error\": \"No data found\"}");
    }
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response, strlen(response));

    mysql_free_result(result);
    mysql_close(mysql);

    return ret;
}

static int POST_iterator(void *coninfo_cls, enum MHD_ValueKind kind, const char *key,
                         const char *filename, const char *content_type,
                         const char *transfer_encoding, const char *data,
                         uint64_t off, size_t size) {
    (void) coninfo_cls;
    (void) key;
    (void) filename;
    (void) content_type;
    (void) transfer_encoding;
    (void) data;
    (void) off;
    (void) size;

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_THREAD_PER_CONNECTION,
                                                 PORT, NULL, NULL, &answer_to_connection,
                                                 NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on http://localhost:%d/\n", PORT);

    getchar();

    int ret = MHD_stop_daemon(daemon);
    return ret;
}


This code requires linking against `libmicrohttpd` and `libmysqlclient`. Compile with:


gcc -o app server.c $(pkg-config --cflags --libs libmicrohttpd) -lmysqlclient