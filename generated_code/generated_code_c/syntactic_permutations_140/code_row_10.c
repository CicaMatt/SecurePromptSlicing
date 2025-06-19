#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Connect to the database
    if (!(mysql_init(&mysql))) {
        printf("Could not initialize the connection object.\n");
        return EXIT_FAILURE;
    }

    mysql_options(&mysql, MYSQL_READ_DEFAULT_GROUP, "mysql");
    if (!(mysql_real_connect(&mysql, NULL, NULL, NULL, NULL, 0, NULL, 0))) {
        printf("Could not connect to the database.\n");
        return EXIT_FAILURE;
    }

    // Execute a query and check it returns false
    if (mysql_query(&mysql, "SELECT * FROM non_existent_table")) {
        printf("Query returned false.\n");
    }

    // Close the database connection
    mysql_close(&mysql);

    return EXIT_SUCCESS;
}