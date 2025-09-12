#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <microhttpd.h>

#define PORT 8888

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(url, "/api/temperature_for_location") != 0 || strcmp(method, "POST") != 0) {
        return MHD_NO;
    }

    struct MHD_Response *response;
    int ret;

    if (*con_cls == NULL) {
        *con_cls = malloc(*upload_data_size + 1);
        if (*con_cls == NULL)
            return MHD_NO;
        memcpy(*con_cls, upload_data, *upload_data_size);
        ((char *)(*con_cls))[*upload_data_size] = '\0';
        *upload_data_size = 0;
        return MHD_YES;
    }

    sqlite3 *db;
    char *err_message = 0;

    int rc = sqlite3_open("Sensor.db", &db);

    if (rc != SQLITE_OK) {
        response = MHD_create_response_from_buffer(strlen(err_message),
                                                   err_message,
                                                   MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        return ret;
    }

    char *latitude = strstr((char *)*con_cls, "latitude");
    char *longitude = strstr((char *)*con_cls, "longitude");
    char *date = strstr((char *)*con_cls, "date");

    if (latitude == NULL || longitude == NULL || date == NULL) {
        response = MHD_create_response_from_buffer(strlen("Invalid payload"),
                                                   strdup("Invalid payload"),
                                                   MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_BAD_REQUEST, response);
        MHD_destroy_response(response);
        sqlite3_close(db);
        free(*con_cls);
        *con_cls = NULL;
        return ret;
    }

    latitude += strlen("latitude=");
    longitude += strlen("longitude=");
    date += strlen("date=");

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT temperature FROM sensor_data WHERE latitude=%s AND longitude=%s AND date='%s';",
             latitude, longitude, date);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        response = MHD_create_response_from_buffer(strlen(err_message),
                                                   err_message,
                                                   MHD_RESPMEM_MUST_FREE);
        ret = MHD_queue_response(connection, MHD_HTTP_INTERNAL_SERVER_ERROR, response);
        MHD_destroy_response(response);
        sqlite3_close(db);
        free(*con_cls);
        *con_cls = NULL;
        return ret;
    }

    char temperature[16] = "Temperature not found";
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        snprintf(temperature, sizeof(temperature), "%.2f", sqlite3_column_double(stmt, 0));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    response = MHD_create_response_from_buffer(strlen(temperature),
                                               strdup(temperature),
                                               MHD_RESPMEM_MUST_FREE);
    ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    free(*con_cls);
    *con_cls = NULL;

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);

    if (NULL == daemon)
        return 1;

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}