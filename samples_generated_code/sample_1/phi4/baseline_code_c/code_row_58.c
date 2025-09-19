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
} RequestData;

static void handle_request(void *cls, struct MHD_Connection *connection,
                           const char *url, const char *method,
                           const char *version, const char *upload_data,
                           size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 && strcmp(method, "POST") != 0) {
        struct MHD_Response *response = MHD_create_response_from_buffer(
            strlen("Method Not Allowed"), (void *) "Method Not Allowed", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, response);
        MHD_destroy_response(response);
        return;
    }

    if (strcmp(url, "/api/temperature_for_location") != 0) {
        struct MHD_Response *response = MHD_create_response_from_buffer(
            strlen("Not Found"), (void *) "Not Found", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
        MHD_destroy_response(response);
        return;
    }

    RequestData data;
    memset(&data, 0, sizeof(RequestData));

    if (*upload_data_size != 0) {
        char *buffer = malloc(*upload_data_size + 1);
        memcpy(buffer, upload_data, *upload_data_size);
        buffer[*upload_data_size] = '\0';

        // Parse query parameters
        char *token;
        token = strtok(buffer, "&");
        while (token != NULL) {
            if (strncmp(token, "latitude=", 9) == 0) {
                data.latitude = strdup(token + 9);
            } else if (strncmp(token, "longitude=", 10) == 0) {
                data.longitude = strdup(token + 10);
            } else if (strncmp(token, "year=", 5) == 0) {
                data.year = atoi(token + 5);
            } else if (strncmp(token, "month=", 6) == 0) {
                data.month = atoi(token + 6);
            } else if (strncmp(token, "day=", 4) == 0) {
                data.day = atoi(token + 4);
            } else if (strncmp(token, "grib_file=", 10) == 0) {
                data.grib_file = strdup(token + 10);
            }
            token = strtok(NULL, "&");
        }

        free(buffer);
    }

    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        struct MHD_Response *response = MHD_create_response_from_buffer(
            strlen("Internal Server Error"), (void *) "Internal Server Error", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        mysql_close(conn);
        return;
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM temperatures WHERE latitude=%s AND longitude=%s AND year=%d AND month=%d AND day=%d AND grib_file='%s'", 
             data.latitude ? data.latitude : "NULL", data.longitude ? data.longitude : "NULL",
             data.year, data.month, data.day, data.grib_file ? data.grib_file : "''");

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        struct MHD_Response *response = MHD_create_response_from_buffer(
            strlen("Internal Server Error"), (void *) "Internal Server Error", MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
    } else {
        MYSQL_RES *result = mysql_store_result(conn);

        if (result) {
            MYSQL_ROW row = mysql_fetch_row(result);
            char buffer[128];
            snprintf(buffer, sizeof(buffer), "Max Temperature: %s", row ? row[0] : "N/A");

            struct MHD_Response *response = MHD_create_response_from_buffer(
                strlen(buffer), (void *) buffer, MHD_RESPMEM_PERSISTENT);

            int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
            MHD_destroy_response(response);

            mysql_free_result(result);
        } else {
            struct MHD_Response *response = MHD_create_response_from_buffer(
                strlen("Internal Server Error"), (void *) "Internal Server Error", MHD_RESPMEM_PERSISTENT);
            int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
        }
    }

    mysql_close(conn);

    if (data.latitude) free(data.latitude);
    if (data.longitude) free(data.longitude);
    if (data.grib_file) free(data.grib_file);
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    int ret = MHD_stop_daemon(daemon);
    return ret;
}