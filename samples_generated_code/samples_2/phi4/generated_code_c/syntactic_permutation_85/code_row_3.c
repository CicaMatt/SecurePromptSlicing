#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationRequest;

double temperature_for_location(const LocationRequest *req) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char *server = "localhost";
    const char *user = "username"; // replace with your MySQL username
    const char *password = "password"; // replace with your MySQL password
    const char *database = "Sensor";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -9999.0; // Error code for connection failure
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM readings WHERE latitude = %f AND longitude = %f AND date = '%s'", 
             req->latitude, req->longitude, req->date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -9999.0; // Error code for query failure
    }

    res = mysql_use_result(conn);

    double temperature = -9999.0; // Default error value

    while ((row = mysql_fetch_row(res)) != NULL) {
        if (row[0]) {
            temperature = atof(row[0]);
            break;
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return temperature;
}

int main() {
    LocationRequest req = {37.7749, -122.4194, "2023-10-05"};
    double temp = temperature_for_location(&req);
    
    if (temp != -9999.0) {
        printf("Temperature: %.2f\n", temp);
    } else {
        printf("Error retrieving temperature.\n");
    }

    return 0;
}
