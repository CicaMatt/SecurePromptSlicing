#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return 0;
}

double temperature_for_location(double latitude, double longitude, const char* date) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[500];
    double temperature = -999.9; // Default value if no data found

    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM sensor_data WHERE latitude = %f AND longitude = %f AND date = '%s';",
             latitude, longitude, date);

    rc = sqlite3_exec(db, sql, callback, &temperature, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    } else {
        printf("Operation done successfully\n");
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char* date = "2023-10-05"; // Example date

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %f\n", temp);

    return 0;
}