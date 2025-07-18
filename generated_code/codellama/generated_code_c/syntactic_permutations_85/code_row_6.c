#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sqlite3.h>

int get_temperature(float latitude, float longitude, int date) {
    sqlite3* db;
    char* errorMessage = 0;
    char query[1024];
    sprintf(query, "SELECT temperature FROM Sensor WHERE latitude=%f AND longitude=%f AND date=%d", latitude, longitude, date);
    int exitCode = sqlite3_open("Sensor.db", &db);
    if (exitCode != SQLITE_OK) {
        printf("%s\n", errorMessage);
        sqlite3_free(errorMessage);
        return 1;
    }
    sqlite3_stmt* statement;
    exitCode = sqlite3_prepare_v2(db, query, -1, &statement, NULL);
    if (exitCode != SQLITE_OK) {
        printf("%s\n", errorMessage);
        sqlite3_free(errorMessage);
        return 1;
    }
    while ((exitCode = sqlite3_step(statement)) == SQLITE_ROW) {
        float temperature = sqlite3_column_double(statement, 0);
        printf("%f", temperature);
    }
    if (exitCode != SQLITE_DONE) {
        printf("%s\n", errorMessage);
        sqlite3_free(errorMessage);
        return 1;
    }
    sqlite3_finalize(statement);
    sqlite3_close(db);
    return 0;
}