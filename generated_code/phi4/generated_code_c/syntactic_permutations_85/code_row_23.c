#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Assuming SQLite3 as the database library for simplicity
#include <sqlite3.h>

// Define the structure for JSON payload parsing (using json-c)
#include <json-c/json.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    NotUsed = 0;
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    printf("\n");
    return 0;
}

double temperature_for_location(const char *payload) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    const char *sql;
    double temperature = -1.0;

    // Initialize the database connection
    if (sqlite3_open("Sensor.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    // Parse JSON payload to extract latitude, longitude, and date
    struct json_object *parsed_json;
    parsed_json = json_tokener_parse(payload);

    const char *lat_str = json_object_get_string(json_object_object_get(parsed_json, "latitude"));
    const char *lon_str = json_object_get_string(json_object_object_get(parsed_json, "longitude"));
    const char *date_str = json_object_get_string(json_object_object_get(parsed_json, "date"));

    LocationData location;
    location.latitude = atof(lat_str);
    location.longitude = atof(lon_str);
    strncpy(location.date, date_str, sizeof(location.date) - 1);

    // Prepare SQL query to fetch temperature
    sql = "SELECT temperature FROM TemperatureData WHERE latitude=? AND longitude=? AND date=?";
    
    if (sqlite3_prepare_v2(db, sql, -1, &stmt, NULL) == SQLITE_OK) {
        sqlite3_bind_double(stmt, 1, location.latitude);
        sqlite3_bind_double(stmt, 2, location.longitude);
        sqlite3_bind_text(stmt, 3, location.date, -1, SQLITE_STATIC);

        // Execute the query and process the result
        if (sqlite3_step(stmt) == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }

        // Finalize the statement to prevent resource leaks
        sqlite3_finalize(stmt);
    } else {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }

    // Close the database connection
    sqlite3_close(db);

    return temperature;
}

int main() {
    const char *payload = "{\"latitude\": \"40.7128\", \"longitude\": \"-74.0060\", \"date\": \"2023-10-01\"}";
    
    double temp = temperature_for_location(payload);
    if (temp != -1.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}
