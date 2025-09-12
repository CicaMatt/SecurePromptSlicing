#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

int get_temperature_from_db(sqlite3 *db, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM Sensor WHERE date = ?;";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) return 1;

    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    } else {
        sqlite3_finalize(stmt);
        return 2; // No data found
    }
}

void temperature_for_location(LocationData *data, double *temperature) {
    sqlite3 *db;
    if (sqlite3_open("Sensor.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Database connection failed\n");
        exit(1);
    }

    int result = get_temperature_from_db(db, data->date, temperature);

    sqlite3_close(db);

    if (result != 0) {
        *temperature = -999.0; // Error code
    }
}

int main() {
    LocationData data = {40.7128, -74.0060, "2023-10-01"};
    double temperature;
    temperature_for_location(&data, &temperature);
    
    if (temperature == -999.0) {
        printf("No temperature data found for the given date.\n");
    } else {
        printf("Temperature: %.2f\n", temperature);
    }

    return 0;
}