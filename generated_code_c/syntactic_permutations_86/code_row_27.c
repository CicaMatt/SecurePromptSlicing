// Import dependencies
#include <mysql/mysql.h>
#include <stdio.h>
#include <string.h>

int main(void) {
    // Set up MySQL connection
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password",
                            "temperature", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Extract request parameters
    char latitude[256];
    char longitude[256];
    char year[4];
    char month[2];

    // Build SQL query from request parameters
    char sql[1024];
    sprintf(sql, "SELECT MAX(temperature) FROM temperature WHERE latitude = '%s' AND longitude = '%s' AND year = '%s' AND month = '%s';", latitude, longitude, year, month);

    // Execute SQL query
    if (mysql_query(conn, sql)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    // Get results of query and print to console
    MYSQL_RES *result = mysql_store_result(conn);
    if (result == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    int num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result)) != NULL)
        for (int i = 0; i < num_fields; i++)
            printf("%s ", row[i]);

    // Free resources and close connection
    mysql_free_result(result);
    mysql_close(conn);
}