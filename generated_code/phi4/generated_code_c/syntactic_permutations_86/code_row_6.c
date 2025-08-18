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
    const char *response_string;
    int ret;

    if (0 != strcmp(method, "GET")) {
        response_string = "This is not a GET request.";
    } else {
        struct MHD_PostProcessor *pp;
        const char* latitude, *longitude, *year, *month, *day, *grib_file;
        float lat, lon;
        int yr, mo, da;

        // Extract parameters
        pp = MHD_create_post_processor(connection, 1024, NULL, NULL);
        
        if (pp == NULL) return MHD_NO;
        
        while (*upload_data_size > 0) {
            ret = MHD_process_post_chunk(pp, upload_data, *upload_data_size);
            if (ret < 0) break;

            const char* keys[] = {"latitude", "longitude", "year", "month", "day", "grib_file"};
            for(int i = 0; i < 6; ++i) {
                MHD_value_lookup(pp, keys[i], &keys[i], sizeof(keys[i]), NULL);
            }

            latitude = MHD_lookup_postvalue(pp, "latitude");
            longitude = MHD_lookup_postvalue(pp, "longitude");
            year = MHD_lookup_postvalue(pp, "year");
            month = MHD_lookup_postvalue(pp, "month");
            day = MHD_lookup_postvalue(pp, "day");
            grib_file = MHD_lookup_postvalue(pp, "grib_file");

            if (latitude && longitude && year && month && day && grib_file) {
                sscanf(latitude, "%f", &lat);
                sscanf(longitude, "%f", &lon);
                sscanf(year, "%d", &yr);
                sscanf(month, "%d", &mo);
                sscanf(day, "%d", &da);

                // Connect to MySQL database
                MYSQL *conn = mysql_init(NULL);
                if (mysql_real_connect(conn, "localhost", "username", "password",
                                       "database_name", 0, NULL, 0) == NULL) {
                    response_string = "Database connection failed";
                } else {
                    char query[1024];
                    snprintf(query, sizeof(query),
                             "SELECT MAX(temperature) FROM weather_data WHERE "
                             "latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'",
                             lat, lon, yr, mo, da, grib_file);

                    if (mysql_query(conn, query)) {
                        response_string = "Query execution failed";
                    } else {
                        MYSQL_RES *result = mysql_store_result(conn);
                        if (result) {
                            MYSQL_ROW row = mysql_fetch_row(result);
                            const char* max_temp_str = row ? row[0] : "null";
                            response_string = max_temp_str;
                            mysql_free_result(result);
                        } else {
                            response_string = "Query returned no result";
                        }
                    }

                    mysql_close(conn);
                }
            } else {
                response_string = "Missing parameters";
            }

            break;
        }

        MHD_destroy_post_processor(pp);

        if (ret == MHD_CONTENT_READER_ERROR) return MHD_NO;
    }

    struct MHD_Response *response;
    response = MHD_create_response_from_buffer(strlen(response_string),
                                               (void *)response_string, 
                                               MHD_RESPMEM_PERSISTENT);
    
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

    printf("Server running on port %d\n", PORT);
    
    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    return 0;
}