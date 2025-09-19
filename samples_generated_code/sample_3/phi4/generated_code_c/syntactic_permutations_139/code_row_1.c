#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "username"  // Replace with actual username
#define PASSWORD "password"  // Replace with actual password
#define DATABASE "database_name"  // Replace with actual database name

int isUserModerator(const char *username) {
    MYSQL conn;
    MYSQL_RES *result;
    MYSQL_ROW row;

    mysql_init(&conn);
    if (!mysql_real_connect(&conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 0; // False
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT role FROM users WHERE username = '%s'", mysql_real_escape_string(&conn, (char *)username));

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 0; // False
    }

    result = mysql_store_result(&conn);
    if (!result) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return 0; // False
    }

    int isModerator = 0;
    while ((row = mysql_fetch_row(result))) {
        if (row[0] && strcmp(row[0], "moderator") == 0) {
            isModerator = 1;
            break;
        }
    }

    mysql_free_result(result);
    mysql_close(&conn);

    return isModerator; // True or False
}

int main() {
    const char *username = "example_user"; // Replace with the username to check
    if (isUserModerator(username)) {
        printf("True\n");
    } else {
        printf("False\n");
    }

    return 0;
}