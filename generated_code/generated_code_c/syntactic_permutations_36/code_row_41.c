#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void login(char* username, char* password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "", "login", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[200];
    sprintf(query, "SELECT * FROM users WHERE username='%s' AND password='%s' LIMIT 1;", username, password);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_use_result(conn);
    row = mysql_fetch_row(res);
    if (row) {
        printf("Logged in successfully!\n");
    } else {
        printf("Invalid username or password.\n");
    }
}

int main() {
    char* username;
    char* password;

    printf("Enter your username: ");
    scanf("%s", &username);
    printf("Enter your password: ");
    scanf("%s", &password);
    login(username, password);
}