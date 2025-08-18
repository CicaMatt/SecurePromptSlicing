#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080
#define MYSQL_USER "user"
#define MYSQL_PASSWORD "password"
#define MYSQL_DATABASE "weatherdb"

struct connection_info_struct {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method, const char *version,
                   const char *upload_data, size_t *upload_data_size, void **con_cls) {
    MYSQL *conn = (MYSQL *) cls;
    struct connection_info_struct *con_info = malloc(sizeof(struct connection_info_struct));
    if (*con_cls == NULL) {
        con_info->latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
        con_info->longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
        con_info->year = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year");
        con_info->month = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month");
        con_info->day = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day");
        con_info->grib_file = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file");

        *con_cls = con_info;
        return MHD_YES;
    }

    if (*upload_data_size != 0) {
        return MHD_YES;
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM temperature_data WHERE latitude='%s' AND longitude='%s' AND year='%s' AND month='%s' AND day='%s' AND grib_file='%s'",
             con_info->latitude, con_info->longitude, con_info->year, con_info->month, con_info->day, con_info->grib_file);

    MYSQL_RES *result;
    MYSQL_ROW row;

    if (mysql_query(conn, query) != 0) {
        mysql_close(conn);
        return MHD_NO;
    }

    result = mysql_store_result(conn);
    if (result == NULL) {
        mysql_close(conn);
        return MHD_NO;
    }

    row = mysql_fetch_row(result);
    char *response_str = "No data found";
    if (row != NULL && strlen(row[0]) > 0) {
        response_str = row[0];
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_str),
                                                                     (void *) response_str,
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    mysql_free_result(result);
    free(con_info);

    return ret;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    if (mysql_real_connect(conn, "localhost", MYSQL_USER, MYSQL_PASSWORD, MYSQL_DATABASE, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_IN_THREAD, PORT, NULL, NULL,
                                                 &handle_request, conn, MHD_OPTION_END);

    if (daemon == NULL) {
        fprintf(stderr, "MHD_start_daemon failed\n");
        mysql_close(conn);
        return 1;
    }

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);

    return 0;
}