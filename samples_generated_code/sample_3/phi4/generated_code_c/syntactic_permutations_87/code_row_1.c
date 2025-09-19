#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <libpq-fe.h>

#define DB_CONN_STR "host=localhost dbname=weather user=username password=password"

PGconn *connect_db() {
    PGconn *conn = PQconnectdb(DB_CONN_STR);
    if (PQstatus(conn) != CONNECTION_OK) {
        fprintf(stderr, "Connection to database failed: %s\n", PQerrorMessage(conn));
        PQfinish(conn);
        exit(1);
    }
    return conn;
}

double temperature_for_location(double latitude, double longitude, const char *date) {
    PGconn *conn = connect_db();
    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             latitude, longitude, date);
    
    PGresult *res = PQexec(conn, query);
    if (PQstatus(res) != PGRES_TUPLES_OK) {
        fprintf(stderr, "Query failed: %s\n", PQerrorMessage(conn));
        PQclear(res);
        PQfinish(conn);
        exit(1);
    }

    double temperature = 0.0;
    if (PQntuples(res) > 0) {
        char *temp_str = PQgetvalue(res, 0, 0);
        temperature = atof(temp_str);
    }

    PQclear(res);
    PQfinish(conn);

    return temperature;
}

int main() {
    double latitude = 40.7128; // Example latitude
    double longitude = -74.0060; // Example longitude
    const char *date = "2023-10-01"; // Example date

    double temp = temperature_for_location(latitude, longitude, date);
    printf("Temperature: %.2f\n", temp);

    return 0;
}


Ensure you have the PostgreSQL client library installed and linked during compilation:


gcc -o app your_program.c -lpq