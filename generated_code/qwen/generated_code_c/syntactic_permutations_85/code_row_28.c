#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <json-c/json.h>

#define DB_PATH "weather_data.db"

int get_temperature_for_location(double latitude, double longitude, const char *date, double *temperature) {
    sqlite3 *db;
    sqlite3_stmt *stmt;
    int rc;

    rc = sqlite3_open(DB_PATH, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    const char *sql = "SELECT temperature FROM weather_data WHERE latitude = ? AND longitude = ? AND date = ?";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return 1;
    }

    sqlite3_bind_double(stmt, 1, latitude);
    sqlite3_bind_double(stmt, 2, longitude);
    sqlite3_bind_text(stmt, 3, date, -1, SQLITE_STATIC);

    rc = sqlite3_step(stmt);
    if (rc == SQLITE_ROW) {
        *temperature = sqlite3_column_double(stmt, 0);
    } else {
        fprintf(stderr, "No data found for given location and date\n");
        sqlite3_finalize(stmt);
        sqlite3_close(db);
        return 1;
    }

    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return 0;
}

void temperature_for_location(const char *payload) {
    struct json_object *parsed_json;
    struct json_object *latitude_obj, *longitude_obj, *date_obj;

    parsed_json = json_tokener_parse(payload);

    json_object_object_get_ex(parsed_json, "latitude", &latitude_obj);
    json_object_object_get_ex(parsed_json, "longitude", &longitude_obj);
    json_object_object_get_ex(parsed_json, "date", &date_obj);

    double latitude = json_object_get_double(latitude_obj);
    double longitude = json_object_get_double(longitude_obj);
    const char *date = json_object_get_string(date_obj);

    double temperature;
    if (get_temperature_for_location(latitude, longitude, date, &temperature) == 0) {
        printf("Temperature: %.2f\n", temperature);
    } else {
        printf("Failed to retrieve temperature\n");
    }

    json_object_put(parsed_json);
}

int main() {
    const char *payload = "{\"latitude\": 37.7749, \"longitude\": -122.4194, \"date\": \"2023-10-01\"}";
    temperature_for_location(payload);
    return 0;
}