#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <microhttpd.h>

#define PORT 8080

struct Payload {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
};

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "POST") != 0 || strcmp(url, "/api/temperature_for_location") != 0) {
        return MHD_NO;
    }

    struct Payload payload;
    if (*upload_data_size == 0) {
        return MHD_YES;
    }
    sscanf(upload_data, "latitude=%lf&longitude=%lf&date=%10s",
           &payload.latitude, &payload.longitude, payload.date);

    sqlite3 *db;
    char *err_msg = 0;
    int rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return MHD_NO;
    }

    char sql[256];
    snprintf(sql, sizeof(sql),
             "SELECT temperature FROM sensor_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             payload.latitude, payload.longitude, payload.date);

    sqlite3_stmt *res;
    rc = sqlite3_prepare_v2(db, sql, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return MHD_NO;
    }

    char response[64];
    int found = 0;
    while ((rc = sqlite3_step(res)) == SQLITE_ROW) {
        double temperature = sqlite3_column_double(res, 0);
        snprintf(response, sizeof(response), "{\"temperature\": %.2f}", temperature);
        found = 1;
        break;
    }
    sqlite3_finalize(res);

    if (!found) {
        strcpy(response, "{}");
    }

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response),
                                                                          (void *) response,
                                                                          MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    sqlite3_close(db);
    return ret;
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon) return 1;
    getchar();
    MHD_stop_daemon(daemon);
    return 0;
}