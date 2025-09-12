#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "your_db_user"
#define DB_PASS "your_db_pass"
#define DB_NAME "your_db_name"

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[50];
    char password[50];
    char query[100];

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User added successfully.\n");

    mysql_close(conn);
    return 0;
}