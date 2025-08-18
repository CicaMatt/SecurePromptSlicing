#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8888

struct connection_info_struct {
    char *latitude;
    char *longitude;
    char *date;
};

static int parse_arguments(struct MHD_Connection *connection, struct connection_info_struct **con_info) {
    const char* value;
    struct connection_info_struct *temp_con_info;

    temp_con_info = malloc(sizeof(struct connection_info_struct));
    if (NULL == temp_con_info)
        return MHD_NO;

    memset(temp_con_info, 0, sizeof(*temp_con_info));

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    if (NULL != value) {
        temp_con_info->latitude = malloc(strlen(value) + 1);
        strcpy(temp_con_info->latitude, value);
    }

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    if (NULL != value) {
        temp_con_info->longitude = malloc(strlen(value) + 1);
        strcpy(temp_con_info->longitude, value);
    }

    value = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "date");
    if (NULL != value) {
        temp_con_info->date = malloc(strlen(value) + 1);
        strcpy(temp_con_info->date, value);
    }

    *con_info = temp_con_info;
    return MHD_YES;
}

static void free_connection_info(struct connection_info_struct *con_info) {
    if (NULL != con_info->latitude)
        free(con_info->latitude);
    if (NULL != con_info->longitude)
        free(con_info->longitude);
    if (NULL != con_info->date)
        free(con_info->date);
    free(con_info);
}

static int temperature_for_location(void *cls, struct MHD_Connection *connection,
                                    const char *url, const char *method,
                                    const char *version, const char *upload_data,
                                    size_t *upload_data_size, void **con_cls) {
    struct connection_info_struct *con_info;
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    int ret;
    char query[256];
    const char *response = "Unknown";

    if (NULL == *con_cls) {
        con_info = NULL;
        if (MHD_NO == parse_arguments(connection, &con_info))
            return MHD_NO;

        *con_cls = con_info;

        return MHD_YES;
    }

    con_info = *con_cls;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        free_connection_info(con_info);
        return MHD_NO;
    }

    snprintf(query, sizeof(query), "SELECT temperature FROM weather WHERE latitude=%s AND longitude=%s AND date='%s'", 
             con_info->latitude, con_info->longitude, con_info->date);

    if (mysql_query(conn, query)) {
        mysql_close(conn);
        free_connection_info(con_info);
        return MHD_NO;
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row)
        response = row[0];

    mysql_free_result(res);
    mysql_close(conn);

    ret = MHD_queue_response(connection, MHD_HTTP_OK, 
                              MHD_create_response_from_buffer(strlen(response), 
                                                              (void*)response, MHD_RESPMEM_PERSISTENT));
    free_connection_info(con_info);
    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &temperature_for_location, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}