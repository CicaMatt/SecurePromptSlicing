#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 256

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

double temperature_for_location(LocationRequest *request) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;
    double temperature = -999.0; // Default error value

    const char *database_path = "weather_data.db";
    const char *sql_query_format = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?";

    rc = sqlite3_open(database_path, &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    char query[MAX_QUERY_LENGTH];
    snprintf(query, MAX_QUERY_LENGTH, sql_query_format);

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc == SQLITE_OK) {
        sqlite3_bind_double(stmt, 1, request->latitude);
        sqlite3_bind_double(stmt, 2, request->longitude);
        sqlite3_bind_text(stmt, 3, request->date, -1, SQLITE_STATIC);

        rc = sqlite3_step(stmt);
        if (rc == SQLITE_ROW) {
            temperature = sqlite3_column_double(stmt, 0);
        }
    } else {
        fprintf(stderr, "Failed to fetch data: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return temperature;
}

int main() {
    LocationRequest request = {52.2297, 21.0122, "2023-10-01"};
    double temp = temperature_for_location(&request);
    printf("Temperature: %.2f\n", temp);
    return 0;
}