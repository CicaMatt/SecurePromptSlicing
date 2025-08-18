#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfo {
    char *latitude;
    char *longitude;
    char *year;
    char *day;
    char *grib_file;
};

void free_connection_info(struct ConnectionInfo *info) {
    free(info->latitude);
    free(info->longitude);
    free(info->year);
    free(info->day);
    free(info->grib_file);
}

int extract_query_params(const char *query_string, struct ConnectionInfo *info) {
    info->latitude = strdup(strstr(query_string, "latitude=") + 9);
    char *end = strchr(info->latitude, '&');
    if (end) *end = '\0';

    info->longitude = strdup(strstr(query_string, "longitude=") + 10);
    end = strchr(info->longitude, '&');
    if (end) *end = '\0';

    info->year = strdup(strstr(query_string, "year=") + 5);
    end = strchr(info->year, '&');
    if (end) *end = '\0';

    info->day = strdup(strstr(query_string, "day=") + 4);
    end = strchr(info->day, '&');
    if (end) *end = '\0';

    info->grib_file = strdup(strstr(query_string, "grib_file=") + 10);
    end = strchr(info->grib_file, '&');
    if (end) *end = '\0';

    return 1;
}

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    struct ConnectionInfo info;
    extract_query_params(MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude"), &info);

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        free_connection_info(&info);
        return MHD_NO;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperatures WHERE latitude=%s AND longitude=%s AND year=%s AND day=%s AND grib_file='%s'",
             info.latitude, info.longitude, info.year, info.day, info.grib_file);

    mysql_query(conn, query);
    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;
    const char *response_content = "Not Found";
    if (result && (row = mysql_fetch_row(result))) {
        response_content = row[0];
    }

    free_connection_info(&info);
    mysql_free_result(result);
    mysql_close(conn);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_content), 
                                                                     (void *)response_content, 
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);
    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}