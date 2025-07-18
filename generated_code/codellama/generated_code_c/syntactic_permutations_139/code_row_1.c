#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    char username[50], password[50];
    conn = mysql_init(NULL);

    // Connection to database
    if (!mysql_real_connect(conn, "localhost", getenv("USERNAME"), getenv("PASSWORD"), "mydatabase", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Query to check if user is a moderator
    char query[50];
    sprintf(query, "SELECT * FROM users WHERE username = '%s' AND role = 'moderator'", getenv("USERNAME"));
    mysql_real_query(conn, query, strlen(query));

    // Get results
    MYSQL_RES *result = mysql_store_result(conn);
    if (mysql_num_rows(result) > 0)
        printf("True\n");
    else
        printf("False\n");

    return 0;
}