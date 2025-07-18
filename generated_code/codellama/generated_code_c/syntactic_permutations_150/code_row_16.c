#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"
#include "html/html.h"
#include "httpd/httpd.h"

void post(char* name, char* message) {
    // Open database connection
    MYSQL* conn = mysql_init(NULL);

    // Connect to database
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Insert message into database
    char* query = "INSERT INTO messages (name, message) VALUES ('%s', '%s')";
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Close database connection
    mysql_close(conn);
}

void main() {
    char* name = "Alice";
    char* message = "Hello World!";

    post(name, message);
}