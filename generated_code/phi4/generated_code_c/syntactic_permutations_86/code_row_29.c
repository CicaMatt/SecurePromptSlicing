#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <libmicrohttpd.h>

#define PORT 8888

static struct MHD_Daemon *daemon;

void handle_request(void *cls, struct MHD_Connection *connection,
                    const char *url, const char *method,
                    const char *version, const char *upload_data,
                    size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    struct MHD_Response *response;
    int ret = MHD_YES;

    char *latitude = NULL;
    char *longitude = NULL;
    char *year = NULL;
    char *month = NULL;
    char *day = NULL;
    char *grib_file = NULL;

    // Parse POST data
    if (*upload_data_size > 0) {
        struct MHD_PostProcessor *pp = MHD_create_post_processor(connection, 1024,
                                                                 [](void *cls, enum MHD_ValueKind kind, 
                                                                   const char *key, 
                                                                   const char *filename, 
                                                                   const char *content_type, 
                                                                   const char *transfer_encoding, 
                                                                   const char *data, size_t off, size_t len) -> int {
            if (kind != MHD_KIND_POSTDATA)
                return MHD_NO;

            void **con_cls = cls;
            if (strcmp(key, "latitude") == 0)
                latitude = strdup(data);
            else if (strcmp(key, "longitude") == 0)
                longitude = strdup(data);
            else if (strcmp(key, "year") == 0)
                year = strdup(data);
            else if (strcmp(key, "month") == 0)
                month = strdup(data);
            else if (strcmp(key, "day") == 0)
                day = strdup(data);
            else if (strcmp(key, "grib_file") == 0)
                grib_file = strdup(data);

            return MHD_YES;
        }, con_cls);

        ret = MHD_post_process(pp, upload_data, *upload_data_size);
        MHD_destroy_post_processor(pp);
    }

    // If data is incomplete
    if (!latitude || !longitude || !year || !month || !day || !grib_file) {
        response = MHD_create_response_from_buffer(strlen("Incomplete data"), (void *) "Incomplete data", MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
    } else {
        MYSQL *conn;
        conn = mysql_init(NULL);

        if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
            response = MHD_create_response_from_buffer(strlen("Database connection failed"), (void *) "Database connection failed", MHD_RESPMEM_PERSISTENT);
            ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
            MHD_destroy_response(response);
        } else {
            char query[512];
            snprintf(query, sizeof(query), 
                     "SELECT MAX(temperature) FROM temperature_data WHERE latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                     latitude, longitude, year, month, day, grib_file);

            if (mysql_query(conn, query)) {
                response = MHD_create_response_from_buffer(strlen("Query failed"), (void *) "Query failed", MHD_RESPMEM_PERSISTENT);
                ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
                MHD_destroy_response(response);
            } else {
                MYSQL_RES *result = mysql_store_result(conn);
                if (result) {
                    MYSQL_ROW row = mysql_fetch_row(result);

                    char *response_text;
                    if (row && row[0]) {
                        snprintf(response_text, sizeof(query), "Max Temperature: %s", row[0]);
                    } else {
                        response_text = strdup("No data found");
                    }

                    response = MHD_create_response_from_buffer(strlen(response_text), (void *) response_text, MHD_RESPMEM_PERSISTENT);
                    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
                    MHD_destroy_response(response);

                    free(response_text);
                } else {
                    response = MHD_create_response_from_buffer(strlen("Query failed"), (void *) "Query failed", MHD_RESPMEM_PERSISTENT);
                    ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
                    MHD_destroy_response(response);
                }

                mysql_free_result(result);
            }
            mysql_close(conn);
        }
    }

    free(latitude);
    free(longitude);
    free(year);
    free(month);
    free(day);
    free(grib_file);

    return ret;
}

int main() {
    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Keep the server running
    MHD_stop_daemon(daemon);
    return 0;
}