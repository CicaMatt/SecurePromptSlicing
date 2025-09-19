#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void handle_request(const char *latitude, const char *longitude, const char *date) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "host", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Prepare the SQL query string
    char query[256];
    snprintf(query, sizeof(query), 
             "SELECT temperature FROM temperatures WHERE latitude = '%s' AND longitude = '%s' AND date = '%s'", 
             latitude, longitude, date);

    // Execute the query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);

    // Fetch the result row and print the temperature
    while ((row = mysql_fetch_row(res)) != NULL) {
        printf("Temperature: %s\n", row[0]);
    }

    // Clean up
    mysql_free_result(res);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <latitude> <longitude> <date>\n", argv[0]);
        return EXIT_FAILURE;
    }

    handle_request(argv[1], argv[2], argv[3]);

    return EXIT_SUCCESS;
}
