#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_RESPONSE_LEN 1024

void handle_request(const char *latitude, const char *longitude, const int year, const int month, const int day, const char *grib_file) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the MySQL database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[512];
    snprintf(query, sizeof(query), 
             "SELECT MAX(temperature) FROM weather_data "
             "WHERE latitude = %f AND longitude = %f AND year = %d AND month = %d AND day = %d AND grib_file = '%s'",
             atof(latitude), atof(longitude), year, month, day, grib_file);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if ((row = mysql_fetch_row(res))) {
        printf("Maximum Temperature: %s°C\n", row[0]);
    } else {
        printf("No data found for the specified parameters.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 7) {
        fprintf(stderr, "Usage: %s <latitude> <longitude> <year> <month> <day> <grib_file>\n", argv[0]);
        exit(1);
    }

    const char *latitude = argv[1];
    const char *longitude = argv[2];
    int year = atoi(argv[3]);
    int month = atoi(argv[4]);
    int day = atoi(argv[5]);
    const char *grib_file = argv[6];

    handle_request(latitude, longitude, year, month, day, grib_file);

    return 0;
}


**Note:** This code assumes that you have a MySQL server running locally with a database and table set up according to the query. Replace `"localhost"`, `"root"`, `"password"`, and `"database_name"` with your actual database connection details. Additionally, ensure that the MySQL client library is installed on your system to compile this program using `gcc`.