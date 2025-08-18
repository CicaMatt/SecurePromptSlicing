#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

typedef struct {
    char *latitude;
    char *longitude;
    int year;
    int month;
    int day;
    char *grib_file;
} LocationData;

static void send_response(struct MHD_Connection *connection, const char *response, size_t response_len) {
    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(response_len, (void *)response, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);
}

static int answer_to_connection(void *cls, struct MHD_Connection *connection, const char *url, const char *method,
                                const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0)
        return MHD_NO;

    LocationData data = {0};
    int ret;
    char *key;
    while ((ret = MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, &key, NULL, &data.latitude,
                                            MHD_OPTION_RETURN_STRING, &data.longitude, MHD_OPTION_RETURN_UINT64, &data.year,
                                            MHD_OPTION_RETURN_UINT64, &data.month, MHD_OPTION_RETURN_UINT64, &data.day,
                                            MHD_OPTION_RETURN_STRING, &data.grib_file, MHD_OPTION_END)) == MHD_YES) {
        if (strcmp(key, "latitude") != 0 && strcmp(key, "longitude") != 0 &&
            strcmp(key, "year") != 0 && strcmp(key, "month") != 0 && strcmp(key, "day") != 0 &&
            strcmp(key, "grib_file") != 0) {
            free(data.latitude);
            free(data.longitude);
            free(data.grib_file);
            return MHD_NO;
        }
    }

    if (ret == MHD_NO)
        return MHD_NO;

    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        send_response(connection, "Database connection failed", strlen("Database connection failed"));
        free(data.latitude);
        free(data.longitude);
        free(data.grib_file);
        mysql_close(conn);
        return MHD_YES;
    }

    char query[512];
    snprintf(query, sizeof(query), "SELECT MAX(temperature) FROM temperatures WHERE latitude=%s AND longitude=%s AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
             data.latitude, data.longitude, data.year, data.month, data.day, data.grib_file);

    if (mysql_query(conn, query)) {
        send_response(connection, "Query execution failed", strlen("Query execution failed"));
        free(data.latitude);
        free(data.longitude);
        free(data.grib_file);
        mysql_close(conn);
        return MHD_YES;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        send_response(connection, "Failed to retrieve query results", strlen("Failed to retrieve query results"));
        free(data.latitude);
        free(data.longitude);
        free(data.grib_file);
        mysql_close(conn);
        return MHD_YES;
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    char response[128];
    if (row && row[0]) {
        snprintf(response, sizeof(response), "Max Temperature: %s", row[0]);
    } else {
        strcpy(response, "No temperature data found");
    }
    send_response(connection, response, strlen(response));

    mysql_free_result(result);
    free(data.latitude);
    free(data.longitude);
    free(data.grib_file);
    mysql_close(conn);

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                                                 &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d...\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}