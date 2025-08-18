#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationData;

void temperature_for_location(LocationData *data) {
    const char *conninfo = "dbname=Sensor user=username password=password host=localhost port=5432";
    PGconn *conn = PQconnectdb(conninfo);

    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query),
             "SELECT temperature FROM temperature_data WHERE latitude = %f AND longitude = %f AND date = '%s'",
             data->latitude, data->longitude, data->date);

    PGresult *res = PQexec(conn, query);

    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    if (PQntuples(res) > 0) {
        char *temperature = PQgetvalue(res, 0, 0);
        printf("Temperature: %s\n", temperature);
    } else {
        printf("No data found for the given location and date.\n");
    }

    PQclear(res);
    PQfinish(conn);
}

int main() {
    LocationData data = {37.7749, -122.4194, "2023-10-01"};
    temperature_for_location(&data);
    return 0;
}


Make sure to replace `username` and `password` with your actual database credentials.