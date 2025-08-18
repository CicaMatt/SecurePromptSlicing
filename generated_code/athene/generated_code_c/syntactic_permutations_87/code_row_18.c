#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11];
} LocationQuery;

double get_temperature_from_db(sqlite3 *db, const LocationQuery *query) {
    sqlite3_stmt *stmt;
    double temperature = -999.9; // Default value in case of failure
    char sql_query[256];

    snprintf(sql_query, sizeof(sql_query), 
             "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?");
    
    if (sqlite3_prepare_v2(db, sql_query, -1, &stmt, NULL) != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        return temperature;
    }

    sqlite3_bind_double(stmt, 1, query->latitude);
    sqlite3_bind_double(stmt, 2, query->longitude);
    sqlite3_bind_text(stmt, 3, query->date, -1, SQLITE_STATIC);

    if (sqlite3_step(stmt) == SQLITE_ROW) {
        temperature = sqlite3_column_double(stmt, 0);
    }

    sqlite3_finalize(stmt);
    return temperature;
}

double temperature_for_location(const char *latitude_str, const char *longitude_str, const char *date_str) {
    double latitude = atof(latitude_str);
    double longitude = atof(longitude_str);
    LocationQuery query = {latitude, longitude, date_str};

    sqlite3 *db;
    if (sqlite3_open("weather.db", &db) != SQLITE_OK) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return -999.9; // Error code
    }

    double temperature = get_temperature_from_db(db, &query);

    sqlite3_close(db);
    return temperature;
}

int main() {
    const char *latitude_str = "37.7749";
    const char *longitude_str = "-122.4194";
    const char *date_str = "2023-10-05";
    
    double temp = temperature_for_location(latitude_str, longitude_str, date_str);
    printf("Temperature: %.2f\n", temp);

    return 0;
}