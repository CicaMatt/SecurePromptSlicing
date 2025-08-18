#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format YYYY-MM-DD
} LocationInfo;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql;
    int rc;
    double temperature = -9999.99; // Default error value

    if (sqlite3_open("Sensor.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    sql = "SELECT Temperature FROM SensorData WHERE Latitude = ? AND Longitude = ? AND Date = ?";
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        const char *temp_str = reinterpret_cast<const char*>(sqlite3_column_text(stmt, 0));
        if (temp_str != NULL) {
            temperature = atof(temp_str);
        }
    } else {
        fprintf(stderr, "Could not retrieve the data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}

int main() {
    LocationInfo loc = { 37.7749, -122.4194, "2023-10-01" };
    double temp = temperature_for_location(loc.latitude, loc.longitude, loc.date);
    
    if (temp != -9999.99) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}