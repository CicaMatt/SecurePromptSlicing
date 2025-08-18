#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    return atoi(argv[0]);
}

int temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[256];
    int temperature = -1;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM sensor_data WHERE latitude = %.6f AND longitude = %.6f AND date = '%s';",
             latitude, longitude, date);

    rc = sqlite3_exec(db, sql, callback, &temperature, &zErrMsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
    }

    sqlite3_close(db);
    return temperature;
}

int main() {
    double latitude = 40.7128;
    double longitude = -74.0060;
    const char *date = "2023-10-05";
    int temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %d\n", temp);
    return 0;
}