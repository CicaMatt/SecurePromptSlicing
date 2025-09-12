#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL* conn;
struct MHD_Response *response;

void init_db() {
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

char* get_temperature(char *latitude, char *longitude, char *year, char *month, char *day, char *grib_file) {
    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = '%s';",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return NULL;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    char *temperature = strdup(row ? row[0] : "No data found");

    mysql_free_result(result);
    return temperature;
}

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    if (strstr(url, "/api/temperature_for_location?") == NULL)
        return MHD_NO;

    char latitude[16] = "", longitude[16] = "", year[5] = "", month[3] = "", day[3] = "", grib_file[256] = "";
    const char *query_str = strchr(url, '?') + 1;
    char *query = strdup(query_str);
    char *token = strtok(query, "&");

    while (token) {
        if (strstr(token, "latitude=")) sscanf(token, "latitude=%[^&]", latitude);
        else if (strstr(token, "longitude=")) sscanf(token, "longitude=%[^&]", longitude);
        else if (strstr(token, "year=")) sscanf(token, "year=%[^&]", year);
        else if (strstr(token, "month=")) sscanf(token, "month=%[^&]", month);
        else if (strstr(token, "day=")) sscanf(token, "day=%[^&]", day);
        else if (strstr(token, "grib_file=")) sscanf(token, "grib_file=%[^&]", grib_file);

        token = strtok(NULL, "&");
    }

    free(query);

    char *temperature = get_temperature(latitude, longitude, year, month, day, grib_file);
    response = MHD_create_response_from_buffer(strlen(temperature), (void*) temperature, MHD_RESPMEM_MUST_FREE);
    return MHD_queue_response(connection, MHD_HTTP_OK, response);
}

int main(int argc, char **argv) {
    init_db();
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    mysql_close(conn);
    MHD_stop_daemon(daemon);
    return 0;
}