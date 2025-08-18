#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_QUERY_LENGTH 1024

typedef struct {
    double latitude;
} Request;

double get_latitude_from_request(Request *request) {
    return request->latitude;
}

int temperature_for_location(Request *request, double *temperature) {
    sqlite3 *db;
    const char *sql;
    char query[MAX_QUERY_LENGTH];
    int rc;

    // Open database connection
    rc = sqlite3_open("weather.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    double lat = get_latitude_from_request(request);

    // Prepare SQL query
    snprintf(query, MAX_QUERY_LENGTH, "SELECT temperature FROM weather WHERE latitude = %.6f", lat);
    
    // Execute the SQL command
    rc = sqlite3_exec(db, query, NULL, 0, &sql);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sql);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_stmt *stmt;
    const char *tail;

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, &tail);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        *temperature = -999.9; // Indicate no data found
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);

    return 0;
}