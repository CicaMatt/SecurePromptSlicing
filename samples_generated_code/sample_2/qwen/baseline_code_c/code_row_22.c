#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <microhttpd.h>

#define PORT 8888

int get_temperature(double latitude, double longitude, const char *date, double *temperature) {
    sqlite3 *db;
    sqlite3_stmt *res;
    int rc;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM sensor_data WHERE latitude = ? AND longitude = ? AND date = ?");

    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_double(res, 1, latitude);
    sqlite3_bind_double(res, 2, longitude);
    sqlite3_bind_text(res, 3, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(res);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(res, 0);
        sqlite3_finalize(res);
        sqlite3_close(db);
        return 0;
    } else {
        sqlite3_finalize(res);
        sqlite3_close(db);
        return -1;
    }
}

int temperature_for_location(struct MHD_Connection *connection) {
    const char *payload = MHD_lookup_connection_value(connection, MHD_CONNECTION_VALUE_POSTPROCESS, "data");
    if (!payload) {
        return MHD_NO;
    }

    double latitude, longitude;
    char date[11];
    sscanf(payload, "%lf,%lf,%s", &latitude, &longitude, date);

    double temperature;
    int rc = get_temperature(latitude, longitude, date, &temperature);
    if (rc != 0) {
        return MHD_NO;
    }

    char response[64];
    snprintf(response, sizeof(response), "{\"temperature\": %f}", temperature);

    struct MHD_Response *mhd_response = MHD_create_response_from_buffer(strlen(response), 
                                                                          (void *)response, 
                                                                          MHD_RESPMEM_MUST_COPY);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, mhd_response);
    MHD_destroy_response(mhd_response);

    return ret;
}

int answer_to_connection(void *cls,
                        struct MHD_Connection *connection,
                        const char *url,
                        const char *method,
                        const char *version,
                        const char *upload_data,
                        size_t *upload_data_size,
                        void **con_cls) {
    if (strcmp(method, "POST") != 0 || strcmp(url, "/api/temperature_for_location") != 0) {
        return MHD_NO;
    }

    return temperature_for_location(connection);
}

int main(int argc, char *argv[]) {
    struct MHD_Daemon *daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY,
                                                 PORT,
                                                 NULL,
                                                 NULL,
                                                 &answer_to_connection,
                                                 NULL,
                                                 MHD_OPTION_END);

    if (NULL == daemon) return 1;

    printf("Server running on port %d\n", PORT);
    getchar();

    MHD_stop_daemon(daemon);

    return 0;
}