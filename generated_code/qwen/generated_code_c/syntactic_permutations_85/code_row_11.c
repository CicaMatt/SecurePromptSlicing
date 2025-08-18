#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define DATABASE "Sensor.db"

int get_temperature_for_date(sqlite3 *db, const char *date, double latitude, double longitude, double *temperature) {
    sqlite3_stmt *stmt;
    const char *sql = "SELECT temperature FROM weather_data WHERE date=? AND latitude=? AND longitude=?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, 0) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    sqlite3_bind_text(stmt, 1, date, -1, SQLITE_STATIC);
    sqlite3_bind_double(stmt, 2, latitude);
    sqlite3_bind_double(stmt, 3, longitude);
    
    int rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else if (rc != SQLITE_DONE) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        return 1;
    }
    
    sqlite3_finalize(stmt);
    return rc == SQLITE_ROW ? 0 : 1;
}

int temperature_for_location(const char *payload, double *temperature) {
    sqlite3 *db;
    if (sqlite3_open(DATABASE, &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return 1;
    }
    
    // Simple payload parsing for demonstration purposes
    char date[20], latitude_str[20], longitude_str[20];
    sscanf(payload, "{\"date\":\"%19[^\"]\",\"latitude\":%19[^,],\"longitude\":%19[^\n]", date, latitude_str, longitude_str);
    
    double latitude = atof(latitude_str);
    double longitude = atof(longitude_str);
    
    int rc = get_temperature_for_date(db, date, latitude, longitude, temperature);
    
    sqlite3_close(db);
    return rc;
}

int main() {
    const char *payload = "{\"date\":\"2023-10-01\",\"latitude\":40.71,\"longitude\":-74.01}";
    double temperature;
    
    if (temperature_for_location(payload, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }
    
    return 0;
}