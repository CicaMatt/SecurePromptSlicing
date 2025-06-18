#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

int main()
{
    // Set up database connection
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL)
    {
        printf("Error initializing database\n");
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "root", "password", "database", 0, NULL, 0) == NULL)
    {
        printf("Error connecting to database: %s\n", mysql_error(conn));
        return 1;
    }

    // Get input from user
    char username[256];
    char password[256];
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);

    // Hash password and insert into database
    char hashed_password[256];
    strcpy(hashed_password, sha1(password));
    char query[512];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hashed_password);
    if (mysql_query(conn, query) != 0)
    {
        printf("Error inserting into database: %s\n", mysql_error(conn));
        return 1;
    }

    // Close database connection and exit
    mysql_close(conn);
    return 0;
}