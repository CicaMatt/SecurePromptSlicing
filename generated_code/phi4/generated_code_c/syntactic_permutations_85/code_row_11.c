#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} Payload;

void temperature_for_location(Payload payload) {
    const char *conninfo = "user=yourusername password=yourpassword dbname=Sensors hostaddr=127.0.0.1 port=5432";
    PGconn *conn;
    PGresult *res;
    char query[256];

    // Connect to the database
    conn = PQconnectdb(conninfo);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }

    // Prepare SQL query
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = %.6f AND longitude = %.6f AND date = '%s'", 
             payload.latitude, payload.longitude, payload.date);

    // Execute the query
    res = PQexec(conn, query);
    if (PQresultStatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Error executing query: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    // Fetch the temperature result
    if (PQntuples(res) > 0) {
        printf("Temperature: %.2f\n", atof(PQgetvalue(res, 0, 0)));
    } else {
        printf("No data found for the given location and date.\n");
    }

    // Clean up
    PQclear(res);
    PQfinish(conn);
}

int main() {
    Payload payload = {37.7749, -122.4194, "2023-10-01"}; // Example data
    temperature_for_location(payload);
    return 0;
}


Make sure to replace `yourusername` and `yourpassword` with your actual PostgreSQL username and password. This code assumes you have a table named `readings` in the database `Sensors`, with columns `latitude`, `longitude`, `date`, and `temperature`.