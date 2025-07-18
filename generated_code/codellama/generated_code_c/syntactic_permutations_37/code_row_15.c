// import required dependencies
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "mysql/mysql.h"

int main(void) {
    // initialize variables
    char username[256];
    char password[256];
    char *query;

    // get the username and password from the user
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // create a connection to the database
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database", 0, NULL, 0)) {
        printf("Error connecting to database");
        return 1;
    }

    // create the query to check if the username and password are in the database
    sprintf(query, "SELECT * FROM users WHERE username = '%s' AND password = '%s'", username, password);

    // execute the query and get the result
    MYSQL_RES *result = mysql_store_result(conn);

    // check if the result is empty, which means the username or password is wrong
    if (mysql_num_rows(result) == 0) {
        printf("Error: username or password is incorrect\n");
        return 1;
    }

    // redirect to success page
    printf("Successfully logged in, redirecting...\n");
    sleep(5);
    return 0;
}