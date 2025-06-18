#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Include the MySQL header file
#include "mysql.h"

int main(void)
{
    // Initialize the variables
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = "localhost";
    char *user = "root";
    char *password = ""; /* set me first */
    char *database = "users";

    // Connect to the database
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0))
    {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Create the users table if it doesn't already exist
    const char *createTableQuery = "CREATE TABLE IF NOT EXISTS users (id INT AUTO_INCREMENT, username VARCHAR(255), password VARCHAR(255))";
    mysql_real_query(conn, createTableQuery, strlen(createTableQuery));

    // Prompt the user for their username and password
    printf("Enter your desired username: ");
    char *username = malloc(100);
    scanf("%s", username);

    printf("Enter your desired password: ");
    char *password = malloc(100);
    scanf("%s", password);

    // Insert the user into the database
    const char *insertUserQuery = "INSERT INTO users (username, password) VALUES ('%s', '%s')";
    mysql_real_query(conn, insertUserQuery, strlen(insertUserQuery));

    // Close the connection to the database
    mysql_close(conn);

    return 0;
}