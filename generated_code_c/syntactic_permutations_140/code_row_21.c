#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <mysql/mysql.h>
int main() {
    MYSQL mysql;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Connect to database 
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "username", 
                             "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return -1;
    }

    // Check for username 
    char *query = "SELECT COUNT(*) FROM users WHERE username='test'";
    if (mysql_query(&mysql, query)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return -1;
    }

    res = mysql_store_result(&mysql);
    row = mysql_fetch_row(res);
    int count = atoi(row[0]);
    if (count > 0) {
        printf("Username exists.\n");
    } else {
        printf("Username does not exist.\n");
    }

    // Clean up 
    mysql_free_result(res);
    mysql_close(&mysql);
    return 0;
}