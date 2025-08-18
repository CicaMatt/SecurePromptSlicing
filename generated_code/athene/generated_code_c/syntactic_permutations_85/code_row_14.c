#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    char location[50];
    char date[12]; // YYYY-MM-DD format
} Payload;

int temperature_for_location(sqlite3 *db, const Payload *payload, int *temperature) {
    sqlite3_stmt *stmt;
    char query[200] = "SELECT temperature FROM Sensor WHERE location=? AND date=?";
    
    if (sqlite3_prepare_v2(db, query, -1, &stmt, 0) != SQLITE_OK) return -1;

    sqlite3_bind_text(stmt, 1, payload->location, -1, SQLITE_STATIC);
    sqlite3_bind_text(stmt, 2, payload->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        *temperature = sqlite3_column_int(stmt, 0);
        sqlite3_finalize(stmt);
        return 0;
    } else {
        sqlite3_finalize(stmt);
        return -1; // No temperature found
    }
}

void handle_request(const char *location, const char *date) {
    sqlite3 *db;
    int rc;
    Payload payload = { .location = "", .date = "" };
    
    strcpy(payload.location, location);
    strcpy(payload.date, date);

    if (sqlite3_open("Sensor.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    int temperature;
    rc = temperature_for_location(db, &payload, &temperature);
    if (rc == 0) {
        printf("Temperature: %d\n", temperature);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    sqlite3_close(db);
}

int main() {
    // Example usage
    handle_request("New York", "2023-10-01");
    return 0;
}