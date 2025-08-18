#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "weather.db"

int get_temperature_for_date(sqlite3 *db, double latitude, double longitude, const char *date, double *temperature) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);
    
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999; // Indicating no data found
    }
    
    sqlite3_finalize(stmt);
    return 0;
}

void temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }
    
    double temperature;
    get_temperature_for_date(db, latitude, longitude, date, &temperature);
    
    printf("Temperature for %.6f, %.6f on %s is: %.2f\n", latitude, longitude, date, temperature);
    
    sqlite3_close(db);
}

int main() {
    // Example payload data
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-05";
    
    temperature_for_location(latitude, longitude, date);
    
    return 0;
}