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
    if (0 != strcmp(method, "GET")) return MHD_NO;

    struct MHD_Response *response;
    const char *lat, *lon, *year, *month, *day, *grib_file;
    long latitude, longitude, yr, mnth, dy;
    
    // Extract query parameters
    if (MHD_YES == parse_url_and_extract_params(url, &lat, &lon, &year, &month, &day, &grib_file)) {
        latitude = atol(lat);
        longitude = atol(lon);
        yr = atol(year);
        mnth = atol(month);
        dy = atol(day);

        MYSQL *conn;
        conn = mysql_init(NULL);

        if (mysql_real_connect(conn, "host", "user", "password",
                               "database", 0, NULL, 0) == NULL) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            response = MHD_create_response_from_buffer(strlen("Database connection error"),
                                                       (void *) "Database connection error", 
                                                       MHD_RESPMEM_PERSISTENT);
        } else {
            char query[512];
            snprintf(query, sizeof(query), 
                     "SELECT MAX(temperature) FROM temperatures WHERE "
                     "latitude=%ld AND longitude=%ld AND year=%ld AND month=%ld AND day=%ld AND grib_file='%s'",
                     latitude, longitude, yr, mnth, dy, grib_file);

            if (mysql_query(conn, query)) {
                fprintf(stderr, "%s\n", mysql_error(conn));
                response = MHD_create_response_from_buffer(strlen("Query execution error"),
                                                           (void *) "Query execution error",
                                                           MHD_RESPMEM_PERSISTENT);
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                if (result) {
                    MYSQL_ROW row = mysql_fetch_row(result);

                    const char *max_temp = row ? row[0] : "No data";
                    response = MHD_create_response_from_buffer(strlen(max_temp),
                                                               (void *) max_temp,
                                                               MHD_RESPMEM_PERSISTENT);
                    
                    mysql_free_result(result);
                } else {
                    fprintf(stderr, "%s\n", mysql_error(conn));
                    response = MHD_create_response_from_buffer(strlen("Result retrieval error"),
                                                               (void *) "Result retrieval error",
                                                               MHD_RESPMEM_PERSISTENT);
                }
            }

            mysql_close(conn);
        }

    } else {
        response = MHD_create_response_from_buffer(strlen("Parameter extraction error"),
                                                   (void *)"Parameter extraction error", 
                                                   MHD_RESPMEM_PERSISTENT);
    }

    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

static int parse_url_and_extract_params(const char *url, const char **lat,
                                        const char **lon, const char **year,
                                        const char **month, const char **day,
                                        const char **grib_file) {
    // This function parses the URL and extracts parameters for latitude, longitude, etc.
    // Implementation of extracting parameters from URL query string is omitted here
    // Placeholder example:
    *lat = "40.7128";
    *lon = "-74.0060";
    *year = "2023";
    *month = "10";
    *day = "12";
    *grib_file = "example.grib2";

    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}