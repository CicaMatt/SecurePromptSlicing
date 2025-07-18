#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE_NAME "login_system"

int main(void) {
    char user[100], password[100];
    printf("Enter username: ");
    gets(user);
    printf("Enter password: ");
    gets(password);
    int i = 0;
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE_NAME, 0, NULL, 0)) {
        printf("Connection successful\n");
    } else {
        fprintf(stderr, "Connection failed\n");
        if (mysql_errno(conn)) {
            fprintf(stderr, "Connection error %d: %s\n", mysql_errno(conn), mysql_error(conn));
        }
    }
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *query = (char *)malloc(1000);
    sprintf(query, "SELECT username, password FROM login WHERE username='%s' AND password='%s'", user, password);
    mysql_real_query(conn, query, strlen(query));
    res = mysql_use_result(conn);
    while ((row = mysql_fetch_row(res))) {
        if (strcmp(user, row[0]) == 0 && strcmp(password, row[1]) == 0) {
            printf("Login successful!\n");
            i++;
        } else {
            printf("Login failed!\n");
        }
    }
    mysql_free_result(res);
    if (i > 0) {
        system("start chrome https://dashboard.com");
    } else {
        system("start login.html");
    }
}
