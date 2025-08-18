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
    if (strcmp(method, "GET") != 0 && strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    struct MHD_Response *response = NULL;
    int ret;

    if (strstr(url, "/api/temperature_for_location")) {
        char query[512];
        snprintf(query, sizeof(query), "%s", url);
        
        // Extract parameters from the URL
        const char *lat_param = strstr(query, "latitude=");
        const char *lon_param = strstr(query, "longitude=");
        const char *year_param = strstr(query, "year=");
        const char *month_param = strstr(query, "month=");
        const char *day_param = strstr(query, "day=");
        const char *grib_file_param = strstr(query, "grib_file=");

        if (!lat_param || !lon_param || !year_param || !month_param || !day_param || !grib_file_param) {
            response = MHD_create_response_from_buffer(strlen("Invalid parameters"),
                                                       (void *) "Invalid parameters", MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        } else {
            char latitude[16], longitude[16], year[6], month[4], day[4], grib_file[256];
            
            sscanf(lat_param + 9, "%15s&longitude=", latitude);
            sscanf(lon_param + 10, "%15s&year=", longitude);
            sscanf(year_param + 5, "%5s&month=", year);
            sscanf(month_param + 6, "%3s&day=", month);
            sscanf(day_param + 4, "%3s&grib_file=", day);
            grib_file_param = strstr(grib_file_param, "=") + 1;
            int len = strlen(grib_file_param);
            if (len > sizeof(grib_file) - 1) len = sizeof(grib_file) - 1;
            strncpy(grib_file, grib_file_param, len);
            grib_file[len] = '\0';

            // Connect to MySQL database
            MYSQL *conn;
            conn = mysql_init(NULL);
            
            if (mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0) == NULL) {
                response = MHD_create_response_from_buffer(strlen("Database connection error"),
                                                           (void *) "Database connection error", MHD_RESPMEM_PERSISTENT);
                ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            } else {
                char query[1024];
                snprintf(query, sizeof(query),
                         "SELECT MAX(temperature) FROM temperature_data "
                         "WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                         latitude, longitude, year, month, day, grib_file);

                if (mysql_query(conn, query)) {
                    response = MHD_create_response_from_buffer(strlen("Query execution error"),
                                                               (void *) "Query execution error", MHD_RESPMEM_PERSISTENT);
                    ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
                } else {
                    MYSQL_RES *result = mysql_store_result(conn);
                    
                    if (result) {
                        MYSQL_ROW row;
                        if ((row = mysql_fetch_row(result))) {
                            char buffer[128];
                            snprintf(buffer, sizeof(buffer), "Max Temperature: %s", row[0]);
                            response = MHD_create_response_from_buffer(strlen(buffer),
                                                                       (void *) buffer, MHD_RESPMEM_PERSISTENT);
                        } else {
                            response = MHD_create_response_from_buffer(strlen("No data found"),
                                                                       (void *) "No data found", MHD_RESPMEM_PERSISTENT);
                        }
                        mysql_free_result(result);
                    } else {
                        response = MHD_create_response_from_buffer(strlen("Query result error"),
                                                                   (void *) "Query result error", MHD_RESPMEM_PERSISTENT);
                    }

                    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                }
                
                mysql_close(conn);
            }
        }
    } else {
        response = MHD_create_response_from_buffer(strlen("Resource not found"),
                                                   (void *) "Resource not found", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_NOT_FOUND, response);
    }

    if (response)
        MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY | MHD_USE_DEBUG,
                              PORT, NULL, NULL, &answer_to_connection, NULL, MHD_OPTION_END);
    
    if (NULL == daemon) return 1;
    
    printf("Server running on port %d\n", PORT);

    getchar(); // Wait for Enter to be pressed

    MHD_stop_daemon(daemon);
    return 0;
}