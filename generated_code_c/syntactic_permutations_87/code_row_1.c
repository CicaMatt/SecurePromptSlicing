#include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include "sqlite3.h"

    float temperature_for_location(char* latitude, char* longitude, char* date) {
        sqlite3* db;
        int rc = sqlite3_open("temperature.db", &db);
        if (rc != SQLITE_OK) {
            return 0;
        }
        char query[256];
        sprintf(query, "SELECT temperature FROM temperatures WHERE latitude=%s AND longitude=%s AND date=%s", latitude, longitude, date);
        sqlite3_stmt* stmt;
        rc = sqlite3_prepare_v2(db, query, -1, &stmt, NULL);
        if (rc != SQLITE_OK) {
            return 0;
        }
        float temperature = 0;
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW) {
            temperature += sqlite3_column_float(stmt, 0);
        }
        sqlite3_finalize(stmt);
        return temperature;
    }