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
    if (strcmp(method, "GET") == 0 || strcmp(method, "POST") == 0) {
        const char *response_string = "<html><body>Request received</body></html>";
        struct MHD_Response *response;
        int ret;

        response = MHD_create_response_from_buffer(strlen(response_string),
                                                   (void *)response_string,
                                                   MHD_RESPMEM_PERSISTENT);
        ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
        MHD_destroy_response(response);

        return ret;
    }
    return MHD_NO; // Method not allowed
}

static void handle_temperature_request(const char *latitude, const char *longitude,
                                       const char *year, const char *month,
                                       const char *day, const char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database",
                            0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT * FROM temperature_data WHERE latitude = '%s' AND longitude = '%s' "
             "AND year = '%s' AND month = '%s' AND day = '%s' AND grib_file = '%s'",
             latitude, longitude, year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    printf("Results:\n");
    while ((row = mysql_fetch_row(res))) {
        printf("%s %s %s %s %s %s\n", row[0], row[1], row[2], row[3], row[4], row[5]);
    }

    mysql_free_result(res);
    mysql_close(conn);
}

static int parse_and_handle_request(const char *url, const char *method,
                                    const char *upload_data) {
    if (strcmp(url, "/api/temperature_for_location") == 0 && 
        (strcmp(method, "GET") == 0 || strcmp(method, "POST") == 0)) {

        // For simplicity, let's assume parameters are passed as query strings for GET
        // or in a simple form body for POST.
        
        char latitude[10], longitude[10], year[5], month[3], day[3], grib_file[50];
        
        if (strcmp(method, "GET") == 0) {
            sscanf(url + strlen("/api/temperature_for_location?"),
                   "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]"
                   "&day=%[^&]&grib_file=%s", latitude, longitude, year, month, day, grib_file);
        } else {
            sscanf(upload_data, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]"
                   "&day=%[^&]&grib_file=%s", latitude, longitude, year, month, day, grib_file);
        }

        handle_temperature_request(latitude, longitude, year, month, day, grib_file);

        return MHD_YES;
    }
    return MHD_NO;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);

    getchar(); // Run until Enter is pressed

    MHD_stop_daemon(daemon);

    return 0;
}


Make sure to install the necessary libraries such as `libmicrohttpd` and MySQL development files before compiling this code. You might need to link against these libraries using `-lmicrohttpd -lmysqlclient`. Adjust database connection parameters (`localhost`, `user`, `password`, `database`) to match your setup.