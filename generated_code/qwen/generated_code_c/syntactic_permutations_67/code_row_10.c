#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char server[] = "localhost";
    char user[] = "your_username";
    char password[] = "your_password";
    char database[] = "your_database";

    char query[100];
    char input[50];

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Enter data to insert: ");
    fgets(input, sizeof(input), stdin);
    input[strcspn(input, "\n")] = '\0'; // Remove newline character

    snprintf(query, sizeof(query), "INSERT INTO your_table (your_column) VALUES ('%s')", mysql_real_escape_string(conn, input));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Data inserted successfully.\n");

    mysql_close(conn);

    return 0;
}