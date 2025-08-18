#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "password"
#define DATABASE "weather_db"

void temperature_for_location(double latitude, double longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[256];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    snprintf(query, sizeof(query), "SELECT temperature FROM temperatures WHERE latitude = %f AND longitude = %f AND date = '%s'", latitude, longitude, date);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No temperature data found for the given location and date.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    // Example usage
    double latitude = 37.7749;
    double longitude = -122.4194;
    const char *date = "2023-10-01";

    temperature_for_location(latitude, longitude, date);

    return 0;
}


Make sure to replace the `SERVER`, `USER`, `PASSWORD`, and `DATABASE` with your actual database credentials. Also, ensure that the MySQL development libraries are installed on your system to compile this program. You can compile it using:


gcc -o temperature_for_location temperature_for_location.c $(mysql_config --cflags --libs)


Run the compiled program with:


./temperature_for_location