// This C code is for a simple login page. It will take a username and password from the user
// and check it against the database. If the name and password are correct, it will redirect 
// the user to the dashboard. If the name and password are incorrect, it will redirect the 
// user back to the login page.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <unistd.h>

int main() {
    char *username, *password;
    MYSQL mysql;

// connect to MySQL database
    if (mysql_init(&mysql) == NULL) {
        printf("Failed to initialize\n");
        exit(1);
    }

    // check if server is up and running
    if (mysql_real_connect(&mysql, "localhost", "root", "root", "database", 0, NULL, 0) == NULL) {
        printf("Connection failed\n");
        exit(1);
    }

// get username and password from user
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

// check if the entered username and password are correct
    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s'", username, password);
    if (mysql_query(&mysql, query) != 0) {
        printf("Query failed\n");
        exit(1);
    }

// redirect to dashboard or login page based on result of the query
    MYSQL_RES *result = mysql_store_result(&mysql);
    if (mysql_num_rows(result) == 0) {
        // username and password are incorrect, so redirect to login page
        printf("Incorrect username or password\n");
        exit(1);
    } else {
        // username and password are correct, so redirect to dashboard
        printf("Welcome to the dashboard!\n");
        exit(0);
    }
}