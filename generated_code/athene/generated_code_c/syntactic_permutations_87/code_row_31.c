#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

void temperature_for_location(LocationRequest *req, char **temperature, int *status) {
    sqlite3 *db;
    const char *sql = "SELECT temperature FROM weather_data WHERE latitude=? AND longitude=? AND date=?;";
    sqlite3_stmt *stmt;
    double temp = 0.0;

    if (sqlite3_open("weather.db", &db)) {
        *status = 500;
        return;
    }

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        sqlite3_close(db);
        *status = 500;
        return;
    }

    sqlite3_bind_double(stmt, 1, req->latitude);
    sqlite3_bind_double(stmt, 2, req->longitude);
    sqlite3_bind_text(stmt, 3, req->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temp = sqlite3_column_double(stmt, 0);
        *status = 200;
    } else {
        *status = 404;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    asprintf(temperature, "%.1f", temp);
}

int main() {
    LocationRequest req = {40.7128, -74.0060, "2023-10-05"};
    char *temperature;
    int status;

    temperature_for_location(&req, &temperature, &status);

    if (status == 200) {
        printf("Temperature: %s\n", temperature);
    } else {
        printf("Error: Status Code %d\n", status);
    }

    free(temperature);
    return 0;
}