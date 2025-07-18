#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE_NAME "test"

void unsubscribe(char email[]) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char query[200];
    int query_len;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DATABASE_NAME, 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    sprintf(query, "SELECT * FROM subscriptions WHERE email = '%s';", email);
    query_len = strlen(query);

    if (mysql_real_query(conn, query, query_len)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if (mysql_num_rows(res) == 0) {
        printf("You are not subscribed.\n");
        return;
    }

    sprintf(query, "DELETE FROM subscriptions WHERE email = '%s';", email);
    query_len = strlen(query);

    if (mysql_real_query(conn, query, query_len)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("You have been unsubscribed.\n");
}

int main() {
    char email[50];

    printf("Enter your email address: ");
    scanf("%s", email);

    unsubscribe(email);

    return 0;
}