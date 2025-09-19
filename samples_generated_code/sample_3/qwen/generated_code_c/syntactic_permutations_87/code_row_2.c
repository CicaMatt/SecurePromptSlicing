#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <microhttpd.h>

#define PORT 8080
#define DB_NAME "weather.db"

int handle_request(void *cls, struct MHD_Connection *connection,
                   const char *url, const char *method,
                   const char *version, const char *upload_data,
                   size_t *upload_data_size, void **con_cls) {
    if (strcmp(method, "GET") != 0 || strcmp(url, "/api/temperature_for_location") != 0) {
        return MHD_NO;
    }

    const char *latitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "latitude");
    const char *longitude = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "longitude");
    const char *date = MHD_lookup_connection_value(connection, MHD_GET_ARGUMENT_KIND, "date");

    if (!latitude || !longitude || !date) {
        return MHD_NO;
    }

    sqlite3 *db;
    int rc = sqlite3_open(DB_NAME, &db);
    if (rc != SQLITE_OK) {
        return MHD_NO;
    }

    char query[512];
    snprintf(query, sizeof(query),
             "SELECT temperature FROM weather_data WHERE latitude=%s AND longitude=%s AND date='%s';",
             latitude, longitude, date);

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        return MHD_NO;
    }

    int step_result = sqlite3_step(stmt);
    const char *temperature = "";
    if (step_result == SQLITE_ROW) {
        temperature = sqlite3_column_text(stmt, 0);
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    struct MHD_Response *response = MHD_create_response_from_buffer(strlen(temperature), (void *)temperature, MHD_RESPMEM_PERSISTENT);
    int ret = MHD_queue_response(connection, MHD_HTTP_OK, response);
    MHD_destroy_response(response);

    return ret;
}

int main() {
    struct MHD_Daemon *daemon;

    daemon = MHD_start_daemon(MHD_USE_SELECT_INTERNALLY, PORT, NULL, NULL,
                              &handle_request, NULL, MHD_OPTION_END);
    if (NULL == daemon)
        return 1;

    printf("Server started on port %d\n", PORT);

    getchar();

    MHD_stop_daemon(daemon);
    return 0;
}