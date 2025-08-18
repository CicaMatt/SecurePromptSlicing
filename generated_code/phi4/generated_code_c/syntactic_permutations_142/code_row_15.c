#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USER "your_username"
#define PASSWORD "your_password"
#define DATABASE "your_database"

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char query[256];
    char email[100];

    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    if (!mysql_real_connect(conn, HOST, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    printf("Enter your email address to unsubscribe: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0'; // Remove newline character

    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE email = '%s'", mysql_real_escape_string(conn, email));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    if (row && atoi(row[0]) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s'", mysql_real_escape_string(conn, email));
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("You have been unsubscribed successfully.\n");
        }
    } else {
        printf("Email address not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


**Note:** Replace `your_username`, `your_password`, and `your_database` with your actual MySQL username, password, and database name. Ensure that you have the MySQL development libraries installed to compile this program. You may need to link against these libraries when compiling using a command like:


gcc -o unsubscribe_program unsubscribe_program.c $(mysql_config --cflags --libs)