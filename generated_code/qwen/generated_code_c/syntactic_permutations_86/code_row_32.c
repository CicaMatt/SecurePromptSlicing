#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

struct ConnectionInfoStruct {
    char *latitude;
    char *longitude;
    char *year;
    char *month;
    char *day;
    char *grib_file;
};

static int
answer_to_connection(void *cls, struct MHD_Connection *connection,
                     const char *url, const char *method,
                     const char *version, const char *upload_data,
                     size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0)
        return MHD_NO;

    struct ConnectionInfoStruct *con_info = malloc(sizeof(struct ConnectionInfoStruct));
    con_info->latitude = NULL;
    con_info->longitude = NULL;
    con_info->year = NULL;
    con_info->month = NULL;
    con_info->day = NULL;
    con_info->grib_file = NULL;

    const char *value;
    if ((value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude")) != NULL) {
        con_info->latitude = strdup(value);
    }
    if ((value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude")) != NULL) {
        con_info->longitude = strdup(value);
    }
    if ((value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "year")) != NULL) {
        con_info->year = strdup(value);
    }
    if ((value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "month")) != NULL) {
        con_info->month = strdup(value);
    }
    if ((value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "day")) != NULL) {
        con_info->day = strdup(value);
    }
    if ((value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "grib_file")) != NULL) {
        con_info->grib_file = strdup(value);
    }

    *con_cls = con_info;

    return MHD_YES;
}

static void
request_completed(void *cls, struct MHD_Connection *connection,
                  void **con_cls, enum MHD_RequestTerminationCode toe) {
    struct ConnectionInfoStruct *con_info = *con_cls;
    if (NULL != con_info) {
        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info->year);
        free(con_info->month);
        free(con_info->day);
        free(con_info->grib_file);
        free(con_info);
    }
}

static int
handle_request(struct MHD_Connection *connection, struct ConnectionInfoStruct *con_info) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return MHD_NO;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude = %s AND longitude = %s AND YEAR(date) = %s AND MONTH(date) = %s AND DAY(date) = %s AND grib_file = '%s'",
             con_info->latitude, con_info->longitude, con_info->year, con_info->month, con_info->day, con_info->grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return MHD_NO;
    }

    res = mysql_use_result(conn);

    struct MHD_Response *response;
    const char *result_message = "No data found";

    if ((row = mysql_fetch_row(res)) != NULL) {
        result_message = row[0] ? row[0] : "No data";
    }

    response = MHD_create_response_from_buffer(strlen(result_message), (void *) result_message, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    mysql_free_result(res);
    mysql_close(conn);

    return ret;
}

int
main(int argc, char **argv) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_NOTIFY_COMPLETED, &request_completed, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}