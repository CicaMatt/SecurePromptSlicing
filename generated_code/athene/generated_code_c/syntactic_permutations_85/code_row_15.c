#include <stdio.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    char location[50];
    char date[20];
} Payload;

int get_temperature_from_db(const char *location, const char *date, double *temperature) {
    sqlite3 *db;
    int rc;
    char sql[100];
    sqlite3_stmt *stmt;

    rc = sqlite3_open("Sensor.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    snprintf(sql, sizeof(sql), "SELECT temperature FROM records WHERE location=? AND date=?;");
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_text(stmt, 1, location, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No temperature found for the given location and date.\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

double temperature_for_location(Payload *payload) {
    double temperature = 0.0;
    get_temperature_from_db(payload->location, payload->date, &temperature);
    return temperature;
}