#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize the MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM weather_data WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
    } else {
        printf("No data found for the given parameters.\n");
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Usage: %s <latitude> <longitude> <date>\n", argv[0]);
        return 1;
    }

    const char *latitude = argv[1];
    const char *longitude = argv[2];
    const char *date = argv[3];

    handle_request(latitude, longitude, date);

    return 0;
}
