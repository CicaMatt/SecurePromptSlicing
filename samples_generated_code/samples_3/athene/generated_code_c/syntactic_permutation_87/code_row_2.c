#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

double temperature_for_location(double latitude, double longitude, const char *date) {
    sqlite3 *db;
    char *err_msg = 0;
    int rc;
    double temperature = -999.9;

    rc = sqlite3_open("weather.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return temperature;
    }

    char sql[256];
    sprintf(sql, "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s';", latitude, longitude, date);

    rc = sqlite3_exec(db, sql, [](void *data, int argc, char **argv, char **azColName) {
        double *temp = (double *)data;
        if (argc > 0 && argv[0]) {
            *temp = atof(argv[0]);
        }
        return 0;
    }, &temperature, &err_msg);

    if (rc != SQLITE_OK ) {
        fprintf(stderr, "Failed to execute query: %s\n", err_msg);
        sqlite3_free(err_msg);
    }

    sqlite3_close(db);
    return temperature;
}