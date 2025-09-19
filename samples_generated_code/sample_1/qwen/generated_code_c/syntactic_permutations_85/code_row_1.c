#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD
} LocationData;

int temperature_for_location(void* payload, int (*send_response)(const char*)) {
    sqlite3 *db;
    char *err_message = 0;
    char query[MAX_QUERY_LENGTH];
    sqlite3_stmt *res;
    LocationData data;

    sscanf(payload, "{\"latitude\": %lf, \"longitude\": %lf, \"date\": \"%10[^\"]\"}", 
           &data.latitude, &data.longitude, data.date);

    int rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        send_response("{\"error\": \"Failed to open database.\"}");
        return 1;
    }

    snprintf(query, MAX_QUERY_LENGTH,
             "SELECT temperature FROM readings WHERE latitude = %lf AND longitude = %lf AND date = '%s';",
             data.latitude, data.longitude, data.date);

    rc = sqlite3_prepare_v2(db, query, -1, &res, 0);
    if (rc != SQLITE_OK) {
        sqlite3_close(db);
        send_response("{\"error\": \"Failed to prepare statement.\"}");
        return 1;
    }

    int step = sqlite3_step(res);
    if (step == SQLITE_ROW) {
        double temperature = sqlite3_column_double(res, 0);
        char response[64];
        snprintf(response, sizeof(response), "{\"temperature\": %lf}", temperature);
        send_response(response);
    } else {
        send_response("{\"error\": \"No data found.\"}");
    }

    sqlite3_finalize(res);
    sqlite3_close(db);

    return 0;
}

int send_dummy_response(const char* response) {
    printf("%s\n", response);
    return 0;
}

int main() {
    const char *payload = "{\"latitude\": 40.7128, \"longitude\": -74.0060, \"date\": \"2023-10-05\"}";
    temperature_for_location((void*)payload, send_dummy_response);
    return 0;
}