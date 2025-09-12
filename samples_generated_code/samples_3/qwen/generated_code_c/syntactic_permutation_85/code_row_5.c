#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

struct connection_info_struct {
    char *latitude;
    char *longitude;
    char *date;
};

int send_response(struct MHD_Connection *connection, const char *data) {
    int ret;
    struct MHD_Response *response;

    response = MHD_create_response_from_buffer(strlen(data), (void*) data, MHD_RESPMEM_PERSISTENT);
    if (!response)
        return MHD_NO;

    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int get_temperature_for_location(void *cls, struct MHD_Connection *connection,
                                 const char *url, const char *method,
                                 const char *version, const char *upload_data,
                                 size_t *upload_data_size, void **con_cls) {
    static int aptr;
    struct connection_info_struct *con_info;

    if (strcmp(method, "POST") != 0)
        return send_response(connection, "{\"error\": \"Invalid request method\"}");

    if (*con_cls == NULL) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (con_info == NULL)
            return MHD_NO;

        con_info->latitude = NULL;
        con_info->longitude = NULL;
        con_info->date = NULL;

        *con_cls = con_info;

        return MHD_YES;
    }

    con_info = *con_cls;

    if (*upload_data_size != 0) {
        if (aptr == 0) {
            char *data_copy = malloc(*upload_data_size + 1);
            memcpy(data_copy, upload_data, *upload_data_size);
            data_copy[*upload_data_size] = '\0';

            sscanf(data_copy, "latitude=%[^&]&longitude=%[^&]&date=%s",
                   con_info->latitude, con_info->longitude, con_info->date);

            free(data_copy);
        }

        aptr++;

        *upload_data_size = 0;

        MYSQL *conn;
        MYSQL_RES *res;
        MYSQL_ROW row;

        conn = mysql_init(NULL);
        if (!mysql_real_connect(conn, "localhost", "user", "password", "Sensor", 0, NULL, 0)) {
            return send_response(connection, "{\"error\": \"Failed to connect to database\"}");
        }

        char query[256];
        snprintf(query, sizeof(query), "SELECT temperature FROM weather_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'",
                 con_info->latitude, con_info->longitude, con_info->date);

        if (mysql_query(conn, query)) {
            mysql_close(conn);
            return send_response(connection, "{\"error\": \"Failed to execute query\"}");
        }

        res = mysql_use_result(conn);

        row = mysql_fetch_row(res);
        char response[128];
        if (row != NULL) {
            snprintf(response, sizeof(response), "{\"temperature\": \"%s\"}", row[0]);
        } else {
            snprintf(response, sizeof(response), "{\"error\": \"No data found\"}");
        }

        mysql_free_result(res);
        mysql_close(conn);

        free(con_info->latitude);
        free(con_info->longitude);
        free(con_info->date);
        free(con_info);

        return send_response(connection, response);
    } else {
        aptr = 0;
        return MHD_YES;
    }
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &get_temperature_for_location, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}