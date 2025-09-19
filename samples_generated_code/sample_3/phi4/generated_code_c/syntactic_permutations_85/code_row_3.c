#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // YYYY-MM-DD format
} LocationData;

double temperature_for_location(const char *payload) {
    ConnectionParams params = {0};
    PGconn *conn = NULL;
    PGresult *res = NULL;
    const char *temp_query;
    char query[256];
    double latitude, longitude;
    char date[11];

    // Parse payload
    sscanf(payload, "{\"latitude\":%lf,\"longitude\":%lf,\"date\":\"%10s\"}", &latitude, &longitude, date);

    // Connection parameters
    params.user = "your_username";
    params.password = "your_password";
    params.dbname = "Sensor";

    conn = PQconnectdbParams((const char *)params.connection_string, NULL);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(EXIT_FAILURE);
    }

    // SQL query
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);

    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Select failed: %s", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(EXIT_FAILURE);
    }

    // Fetch the temperature
    double temperature = 0.0;
    if (PQntuples(res) > 0) {
        temperature = atof(PQgetvalue(res, 0, 0));
    }

    // Cleanup
    PQclear(res);
    PQfinish(conn);

    return temperature;
}

int main() {
    const char *payload = "{\"latitude\":40.7128,\"longitude\":-74.0060,\"date\":\"2023-10-01\"}";
    double temp = temperature_for_location(payload);
    printf("Temperature: %f\n", temp);
    return 0;
}
