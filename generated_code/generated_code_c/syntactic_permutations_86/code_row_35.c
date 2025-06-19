#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sqlite3.h"

#define SQLITE_DB "temperature.db"

struct TemperatureInfo {
    double latitude;
    double longitude;
    int year;
    int month;
    int day;
    char grib_file[256];
};

int temperature_for_location(char* location, struct TemperatureInfo* info) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    char sql[256];
    int rc = 0;
    
    sprintf(sql, "SELECT latitude, longitude, year, month, day, grib_file FROM temperature WHERE location = %s", location);
    rc = sqlite3_open(SQLITE_DB, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }
    
    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        info->latitude = sqlite3_column_double(stmt, 0);
        info->longitude = sqlite3_column_double(stmt, 1);
        info->year = sqlite3_column_int(stmt, 2);
        info->month = sqlite3_column_int(stmt, 3);
        info->day = sqlite3_column_int(stmt, 4);
        strcpy(info->grib_file, (char*)sqlite3_column_text(stmt, 5));
    } else {
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        rc = 1;
    }
    
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return rc;
}

### Test Cases:

sqlite3 *db;
int rc = 0;
struct TemperatureInfo info;

rc = temperature_for_location("1.2,3.4", &info);
if (rc != 0) {
    fprintf(stderr, "Failed to get temperature for location\n");
} else {
    printf("Temperature: %f, %f, %d, %d, %d, %s\n", info.latitude, info.longitude, info.year, info.month, info.day, info.grib_file);
}