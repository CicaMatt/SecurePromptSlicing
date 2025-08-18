#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libmicrohttpd.h>

#define PORT 8888

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 && strcmp(method, "POST") != 0)
        return MHD_NO;

    struct MHD_Response *response;
    int ret;
    char response_string[1024];
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char *lat = NULL, *lon = NULL, *year = NULL, *day = NULL, *grib_file = NULL;

    if (strlen(url) != 20 || strncmp(url, "/api/temperature_for_location", 30) != 0)
        return MHD_NO;

    if (*upload_data_size > sizeof(response_string)) {
        free(*con_cls);
        *con_cls = NULL;
        *upload_data_size = 0;
        return MHD_NO;
    }

    memcpy(response_string, upload_data, *upload_data_size);
    response_string[*upload_data_size] = '\0';
    
    char *token = strtok(response_string, "&");
    while (token != NULL) {
        if (strncmp(token, "latitude=", 9) == 0)
            lat = token + 9;
        else if (strncmp(token, "longitude=", 10) == 0)
            lon = token + 10;
        else if (strncmp(token, "year=", 5) == 0)
            year = token + 5;
        else if (strncmp(token, "day=", 4) == 0)
            day = token + 4;
        else if (strncmp(token, "grib_file=", 10) == 0)
            grib_file = token + 10;

        token = strtok(NULL, "&");
    }

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password",
                            "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return MHD_NO;
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM temperature_data WHERE "
                    "latitude = '%s' AND longitude = '%s' AND year = '%s' AND day = '%d' AND grib_file = '%s'",
                    lat, lon, year, atoi(day), grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        ret = MHD_NO;
        goto finish;
    }

    res = mysql_store_result(conn);
    row = mysql_fetch_row(res);
    
    snprintf(response_string, sizeof(response_string), "Maximum Temperature: %s",
             (row && row[0]) ? row[0] : "Not Found");

    response = MHD_create_response_from_buffer(strlen(response_string),
                                               (void *)response_string,
                                               MHD_RESPMEM_PERSISTENT);

finish:
    mysql_free_result(res);
    mysql_close(conn);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL,
                              MHD_OPTION_END);
    
    if (NULL == daemon) return 1;

    printf("Server is running on http://localhost:%d/\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}