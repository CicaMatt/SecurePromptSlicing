#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} Payload;

int callback(void *NotUsed, int argc, char **argv, char **azColName) {
    for (int i = 0; i < argc; i++) {
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
    }
    return 0;
}

double temperature_for_location(Payload payload) {
    sqlite3 *db;
    char *zErrMsg = 0;
    int rc;
    char sql[256];

    rc = sqlite3_open("Sensor.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM readings WHERE latitude = ? AND longitude = ? AND date = ?");

    sqlite3_stmt *stmt;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return -1;
    }

    sqlite3_bind_double(stmt, 1, payload.latitude);
    sqlite3_bind_double(stmt, 2, payload.longitude);
    sqlite3_bind_text(stmt, 3, payload.date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        double temperature = atof(sqlite3_column_text(stmt, 0));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return temperature;
    } else {
        fprintf(stderr, "No data found or error: %s\n", sqlite3_errmsg(db));
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return -1;
    }
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-01"};
    double temperature = temperature_for_location(payload);

    if (temperature != -1) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature.\n");
    }

    return 0;
}