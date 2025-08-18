#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "your_host"
#define DB_USER "your_user"
#define DB_PASS "your_pass"
#define DB_NAME "your_db"

void unsubscribe(char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char *server = DB_HOST;
    char user[100] = DB_USER;
    char password[100] = DB_PASS; 
    char database[100] = DB_NAME;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    sprintf(query, "SELECT email FROM users WHERE email='%s'", email);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res && mysql_num_rows(res) > 0) {
        sprintf(query, "DELETE FROM users WHERE email='%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("You have been successfully unsubscribed.\n");
        }
    } else {
        printf("The email address is not subscribed.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[100];
    printf("Enter your email to unsubscribe: ");
    scanf("%99s", email);

    unsubscribe(email);

    return 0;
}