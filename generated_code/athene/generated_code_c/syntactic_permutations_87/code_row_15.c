#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationRequest;

double get_temperature_from_db(double lat, double lon, const char *date) {
    sqlite3 *db;
    int rc;
    double temperature = 0.0;

    rc = sqlite3_open("temperature.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -1;
    }

    char sql[256];
    snprintf(sql, sizeof(sql), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s';",
             lat, lon, date);

    rc = sqlite3_exec(db, sql, [](void *data, int argc, char **argv, char **azColName) -> int {
        double *temp = (double *)data;
        *temp = atof(argv[0]);
        return 0;
    }, &temperature, NULL);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    }

    sqlite3_close(db);
    return temperature;
}

double temperature_for_location(LocationRequest *req) {
    return get_temperature_from_db(req->latitude, req->longitude, req->date);
}