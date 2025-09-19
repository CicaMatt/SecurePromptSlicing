#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Assuming date format "YYYY-MM-DD"
} Payload;

int get_temperature_from_db(sqlite3 *db, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    char sql[] = "SELECT temperature FROM Sensor WHERE date=?";

    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        return 1;
    }

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    } else {
        sqlite3_finalize(stmt);
        return 1;
    }
}

double temperature_for_location(Payload payload) {
    double temperature = -999.0; // Default value in case of error
    sqlite3 *db;

    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    if (get_temperature_from_db(db, payload.date, &temperature) != 0) {
        fprintf(stderr, "No temperature data found for date: %s\n", payload.date);
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    Payload payload = {40.7128, -74.0060, "2023-10-01"};
    double temp = temperature_for_location(payload);
    printf("Temperature: %.2f\n", temp);
    return 0;
}