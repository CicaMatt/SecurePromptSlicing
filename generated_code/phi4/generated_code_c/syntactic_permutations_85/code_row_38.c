#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming SQLite3 library is used
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationData;

// Function to get temperature from the database
int fetch_temperature(sqlite3 *db, const char *latitude, const char *longitude, const char *date, double *temperature) {
    char sql[256];
    snprintf(sql, sizeof(sql), "SELECT temperature FROM weather_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", latitude, longitude, date);

    sqlite3_stmt *stmt;
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "Failed to fetch temperature: %s\n", sqlite3_errmsg(db));
        return 0;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
        sqlite3_finalize(stmt);
        return 1;
    }

    fprintf(stderr, "No data found for the given location and date.\n");
    sqlite3_finalize(stmt);
    return 0;
}

void temperature_for_location(LocationData loc_data) {
    sqlite3 *db;
    if (sqlite3_open("weather_database.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    }

    double temperature = 0.0;
    if (!fetch_temperature(db, dbl2str(loc_data.latitude), dbl2str(loc_data.longitude), loc_data.date, &temperature)) {
        printf("Temperature data not available.\n");
    } else {
        printf("Temperature: %.2f°C\n", temperature);
    }

    sqlite3_close(db);
}

// Helper function to convert double to string
char* dbl2str(double value) {
    static char buffer[32];
    snprintf(buffer, sizeof(buffer), "%lf", value);
    return buffer;
}

int main() {
    // Example usage:
    LocationData loc_data = {37.7749, -122.4194, "2023-10-01"};
    temperature_for_location(loc_data);

    return 0;
}


**Note:** Make sure to have the SQLite library installed and properly linked when compiling this code. The database file `weather_database.db` should exist with a table named `weather_data` containing columns for `latitude`, `longitude`, `date`, and `temperature`.