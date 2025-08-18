#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <microhttpd.h>

#define PORT 8080

MYSQL *conn;

int answer_to_connection(void *cls, struct MHD_Connection *connection,
                         const char *url, const char *method,
                         const char *version, const char *upload_data,
                         size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0 || strcmp(url, "/api/temperature_for_location") != 0)
        return MHD_NO;

    static int aptr;
    struct connection_info_struct *con_info = *con_cls;

    if (NULL == con_info) {
        con_info = malloc(sizeof(struct connection_info_struct));
        if (NULL == con_info)
            return MHD_NO;
        memset(con_info, 0, sizeof(struct connection_info_struct));
        *con_cls = con_info;
        aptr = 0;
        return MHD_YES;
    }

    if (aptr == 0) {
        size_t to_read, max;
        const char* upload_data_end;

        upload_data_end = upload_data + *upload_data_size;
        to_read = upload_data_end - upload_data;
        max = sizeof(con_info->value) - con_info->offset;
        if (to_read >= max)
            to_read = max - 1;

        strncpy(&con_info->value[con_info->offset], upload_data, to_read);
        con_info->offset += to_read;

        if (upload_data_end == upload_data + *upload_data_size) {
            aptr = 1;
        } else {
            return MHD_YES;
        }
    }

    char latitude[20], longitude[20], year[5], month[3], day[3], grib_file[100];
    sscanf(con_info->value, "latitude=%[^&]&longitude=%[^&]&year=%[^&]&month=%[^&]&day=%[^&]&grib_file=%s",
           latitude, longitude, year, month, day, grib_file);

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT MAX(temperature) FROM weather_data WHERE latitude=%.4f AND longitude=%.4f AND YEAR(date)=%s AND MONTH(date)=%s AND DAY(date)=%s AND grib_file='%s'",
             atof(latitude), atof(longitude), year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        const char *error = mysql_error(conn);
        struct MHD_Response *response = MHD_create_response_from_buffer(strlen(error),
                                                                         (void *) error,
                                                                         MHD_RESPMEM_PERSISTENT);
        int ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    MYSQL_RES *result = mysql_store_result(conn);
    MYSQL_ROW row;

    char response_buffer[256];
    if ((row = mysql_fetch_row(result))) {
        snprintf(response_buffer, sizeof(response_buffer), "{\"max_temperature\": \"%s\"}", row[0]);
    } else {
        snprintf(response_buffer, sizeof(response_buffer), "{\"max_temperature\": \"null\"}");
    }

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(response_buffer),
                                                                     (void *) response_buffer,
                                                                     MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    mysql_free_result(result);
    free(con_info);
    return ret;
}

struct connection_info_struct {
    char *value;
    size_t offset;
};

int main() {
    struct MHD_Daemon *daemon;

    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, "localhost", "user", "password",
                           "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &answer_to_connection, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    mysql_close(conn);
    return 0;
}