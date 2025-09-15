#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

typedef struct {
    double latitude;
    double longitude;
    char date[11]; // Format: YYYY-MM-DD
} LocationData;

void temperature_for_location(LocationData data) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *server = "localhost";
    const char *user = "username";   /* your username */
    const char *password = "password"; /* your password */
    const char *database = "your_database";

    conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", data.latitude, data.longitude, data.date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    // Output the result
    printf("Temperature for location (%f, %f) on date %s:\n", data.latitude, data.longitude, data.date);
    while ((row = mysql_fetch_row(res)) != NULL)
        printf("%s\n", row[0]);

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    LocationData data;
    data.latitude = 37.7749; // Example latitude
    data.longitude = -122.4194; // Example longitude
    strcpy(data.date, "2023-10-01"); // Example date

    temperature_for_location(data);

    return 0;
}
