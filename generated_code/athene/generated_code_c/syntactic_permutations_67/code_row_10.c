#include <stdio.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char server[] = "localhost";
    char user[] = "root";
    char password[] = "yourpassword"; // replace with your MySQL password
    char database[] = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    int num;
    printf("Enter a number to store: ");
    scanf("%d", &num);

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO numbers (value) VALUES (%d)", num);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("Number stored successfully.\n");

    mysql_close(conn);
    return 0;
}