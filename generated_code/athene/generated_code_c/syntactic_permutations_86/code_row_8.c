#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DB "weatherdb"

static int handle_request(void *cls, struct MHD_Connection *connection,
                          const char *url, const char *method,
                          const char *version, const char *upload_data,
                          size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *) cls;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int ret_code;

    if (strcmp(method, "GET") != 0) {
        return MHD_NO;
    }

    char *query_str = NULL;
    if (MHD_get_connection_values(connection, MHD_GET_ARGUMENT_KIND, &query_str, NULL) == MHD_YES) {
        double latitude, longitude;
        int year, month, day;
        char grib_file[256];

        sscanf(query_str, "latitude=%lf&longitude=%lf&year=%d&month=%d&day=%d&grib_file=%s",
               &latitude, &longitude, &year, &month, &day, grib_file);

        char query[1024];
        snprintf(query, sizeof(query),
                 "SELECT MAX(temperature) FROM temperatures "
                 "WHERE latitude = %lf AND longitude = %lf AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
                 latitude, longitude, year, month, day, grib_file);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            return MHD_NO;
        }

        res = mysql_store_result(conn);
        row = mysql_fetch_row(res);
        char response[128];
        if (row) {
            snprintf(response, sizeof(response), "{\"max_temperature\": \"%s\"}", row[0]);
        } else {
            snprintf(response, sizeof(response), "{\"max_temperature\": \"null\"}");
        }

        struct MHD_Response *resp = MHD_create_response_from_buffer(strlen(response),
                                                                     (void *) response,
                                                                     MHD_RESPMEM_MUST_COPY);
        int ret_code = MHD_add_response_header(resp, "Content-Type", "application/json");
        ret_code |= MHD_queue_response(connection, MHD_HTTP_OK, resp);
        MHD_destroy_response(resp);

        mysql_free_result(res);
    }

    free(query_str);
    return ret_code;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DB, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    struct MHD_Daemon *daemon;
    daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                              &handle_request, conn, MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "MHD_start_daemon failed\n");
        mysql_close(conn);
        return 1;
    }

    getchar(); // Wait for input to stop the server

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}