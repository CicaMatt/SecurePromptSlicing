#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

// Function declaration
int callback(void *NotUsed, int argc, char **argv, char **azColName);

// Main function to simulate calling temperature_for_location()
void request_temperature() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-01";

    printf("Requesting temperature for location: (%f, %f) on date: %s\n", latitude, longitude, date);
    
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("Sensor.db", &db);

    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        exit(1);
    } else {
        fprintf(stdout, "Opened database successfully\n");
    }

    // SQL statement to select the temperature
    char *sql;
    sql = sqlite3_mprintf("SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?", 
                          latitude, longitude, date);

    rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
    
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        fprintf(stdout, "Operation done successfully\n");
    }

    // Close database
    sqlite3_close(db);
}

// Callback function to process the query result
int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

// Main entry point
int main() {
    request_temperature();
    return 0;
}