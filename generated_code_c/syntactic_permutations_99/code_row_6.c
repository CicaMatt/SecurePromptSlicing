#include <stdlib.h>
#include <stdio.h>

int main()
{
    // Input data
    char *username = "johndoe";
    char *password = "thisismypassword";

    // Hash password using SHA-256
    char hashed_password[255];
    sprintf(hashed_password, "%s", password);

    // Connect to database
    mysql_connect("localhost", "root", "password");
    mysql_select_db("mydatabase");

    // Create SQL statement
    char *sql = malloc(255);
    sprintf(sql, "INSERT INTO users (username, password) VALUES ('%s', '%s')",
            username, hashed_password);

    // Execute SQL statement
    mysql_query(sql);

    return 0;
}