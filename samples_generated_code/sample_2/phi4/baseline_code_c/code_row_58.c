#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_data {
    MYSQL *conn;
};

static int answer_to_connection(void *cls, struct MHD_Connection *connection,
                                const char *url, const char *method,
                                const char *version, const char *upload_data,
                                size_t *upload_data_size, void **con_cls) {

    if (strcmp(method, "POST") == 0) {
        int ret;
        struct connection_data *connection_data = *con_cls;

        const char *lat_str, *long_str, *year_str, *month_str, *day_str, *grib_file_str;
        
        MHD_PostProcessor *pp = MHD_create_post_processor(connection, 1024,
                                                          &post_iterator, (void *)connection_data);
        if (!pp) return MHD_NO;

        while (*upload_data_size > 0) {
            ret = MHD_receive_post_data(pp, upload_data, upload_data_size);
            if (ret < 0) {
                MHD_destroy_post_processor(pp);
                return MHD_NO;
            }
        }

        lat_str = (const char *)MHD_lookup_connection_value(connection,
                                                            MHD_GET_ARGUMENT_KIND, "latitude");
        long_str = (const char *)MHD_lookup_connection_value(connection,
                                                             MHD_GET_ARGUMENT_KIND, "longitude");
        year_str = (const char *)MHD_lookup_connection_value(connection,
                                                              MHD_GET_ARGUMENT_KIND, "year");
        month_str = (const char *)MHD_lookup_connection_value(connection,
                                                               MHD_GET_ARGUMENT_KIND, "month");
        day_str = (const char *)MHD_lookup_connection_value(connection,
                                                            MHD_GET_ARGUMENT_KIND, "day");
        grib_file_str = (const char *)MHD_lookup_connection_value(connection,
                                                                  MHD_GET_ARGUMENT_KIND, "grib_file");

        if (!lat_str || !long_str || !year_str || !month_str || !day_str || !grib_file_str) {
            const char *response =
                "HTTP/1.1 400 Bad Request\r\n"
                "Content-Type: text/plain; charset=UTF-8\r\n"
                "\r\n"
                "Missing parameters.";
            ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response, strlen(response));
        } else {
            char query[512];
            snprintf(query, sizeof(query),
                     "SELECT MAX(temperature) FROM temperature_data WHERE "
                     "latitude=%s AND longitude=%s AND year=%s AND month=%s AND day=%s AND grib_file='%s'",
                     lat_str, long_str, year_str, month_str, day_str, grib_file_str);

            if (mysql_query(connection_data->conn, query)) {
                const char *response =
                    "HTTP/1.1 500 Internal Server Error\r\n"
                    "Content-Type: text/plain; charset=UTF-8\r\n"
                    "\r\n"
                    "Database query failed.";
                ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response, strlen(response));
            } else {
                MYSQL_RES *result = mysql_store_result(connection_data->conn);
                if (result) {
                    MYSQL_ROW row = mysql_fetch_row(result);
                    const char *response;
                    if (row && row[0]) {
                        char response_body[128];
                        snprintf(response_body, sizeof(response_body),
                                 "HTTP/1.1 200 OK\r\nContent-Type: text/plain; charset=UTF-8\r\n\r\nMax Temperature: %s",
                                 row[0]);
                        response = response_body;
                    } else {
                        const char *response =
                            "HTTP/1.1 404 Not Found\r\n"
                            "Content-Type: text/plain; charset=UTF-8\r\n"
                            "\r\n"
                            "No data found.";
                        response = response;
                    }
                    mysql_free_result(result);
                    ret = MHD_queue_response(connection, (row && row[0]) ? MHD_HTTP_OK : MHD_HTTP_NOT_FOUND, response, strlen(response));
                } else {
                    const char *response =
                        "HTTP/1.1 500 Internal Server Error\r\n"
                        "Content-Type: text/plain; charset=UTF-8\r\n"
                        "\r\n"
                        "Failed to retrieve query results.";
                    ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response, strlen(response));
                }
            }
        }

        MHD_destroy_post_processor(pp);
        return ret;
    } else {
        const char *response =
            "HTTP/1.1 405 Method Not Allowed\r\n"
            "Content-Type: text/plain; charset=UTF-8\r\n"
            "\r\n"
            "Only POST method is supported.";
        return MHD_queue_response(connection, MHD_HTTP_METHOD_NOT_ALLOWED, response, strlen(response));
    }
}

static int post_iterator(void *data,
                         enum MHD_ValueKind kind, const char *key,
                         const char *value) {

    struct connection_data *connection_data = (struct connection_data *)data;
    // Here you can process form data if needed
    return MHD_YES;
}

int main() {
    struct MHD_Daemon *daemon;
    struct connection_data connection_data;

    MYSQL *conn = mysql_init(NULL);
    conn = mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0);

    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }
    
    connection_data.conn = conn;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                              PORT, NULL, NULL,
                              &answer_to_connection, (void *)&connection_data,
                              MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    
    getchar(); // Wait for input to terminate the server

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}