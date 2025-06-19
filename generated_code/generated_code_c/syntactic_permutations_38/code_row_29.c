#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql.h"
 
void print_user(MYSQL_ROW row, MYSQL_FIELD *field)
{
    // Print one row
    unsigned int field_count = mysql_num_fields(result);
    for (int i = 0; i < field_count; i++) {
        printf("%*s ", field[i].max_length, row[i] ? row[i] : "NULL");
    }
    putchar('\n');
}
 
int main(int argc, char **argv)
{
    MYSQL *mysql;
    // Initialize the database connection.
    mysql = mysql_init(NULL);
    if (mysql == NULL) {
        printf("Error: %s\n", mysql_error(mysql));
        exit(1);
    }
 
    // Connect to the database.
    if (mysql_real_connect(mysql, "localhost", "user", "password",
                           "database", 0, NULL, 0) == NULL) {
        printf("Error: %s\n", mysql_error(mysql));
        exit(1);
    }
 
    // Execute the SQL query.
    if (mysql_query(mysql, "SELECT * FROM users WHERE name = 'username' AND password = 'password'")) {
        printf("Error: %s\n", mysql_error(mysql));
        exit(1);
    }
 
    // Get the result set.
    MYSQL_RES *result = mysql_store_result(mysql);
    if (result == NULL) {
        printf("Error: %s\n", mysql_error(mysql));
        exit(1);
    }
 
    // Print out the fields and rows of the result set.
    MYSQL_ROW row;
    MYSQL_FIELD *field;
    unsigned int num_fields = mysql_num_fields(result);
    while ((row = mysql_fetch_row(result))) {
        for (int i = 0; i < num_fields; i++) {
            field = mysql_fetch_field(result);
            print_user(row, field);
        }
    }
 
    // Free the result set and database connection.
    mysql_free_result(result);
    mysql_close(mysql);
    return 0;
}