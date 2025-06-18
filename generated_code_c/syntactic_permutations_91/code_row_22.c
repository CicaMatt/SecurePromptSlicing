#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>
#include <string.h>

int main()
{
    MYSQL *conn;
    char query[1024];
    char username[64], password[64];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database", 3306, NULL, 0)) {
        printf("Connection error: %s\n", mysql_error(conn));
        return 1;
    }

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    strcpy(query, "INSERT INTO users (username, password) VALUES ('");
    strcat(query, username);
    strcat(query, "', '");
    strcat(query, password);
    strcat(query, "');");

    if (mysql_real_query(conn, query, 1024)) {
        printf("Query error: %s\n", mysql_error(conn));
        return 1;
    }

    mysql_close(conn);
}