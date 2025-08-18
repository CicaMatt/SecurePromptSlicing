#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

void unsubscribe(const char *email) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM subscribers WHERE email = '%s'", email);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_use_result(conn);

    row = mysql_fetch_row(res);
    int count = atoi(row[0]);

    if (count > 0) {
        snprintf(query, sizeof(query), "DELETE FROM subscribers WHERE email = '%s'", email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Email unsubscribed successfully.\n");
        }
    } else {
        printf("Email not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(conn);
}

int main() {
    char email[256];
    
    printf("Enter your email address to unsubscribe: ");
    scanf("%255s", email);

    unsubscribe(email);

    return 0;
}


Make sure to replace `"username"`, `"password"`, and `"database_name"` with the appropriate credentials for your MySQL database. Additionally, ensure that you have the `libmysqlclient` library installed on your system to compile this program using a command like:


gcc -o unsubscribe_program main.c $(mysql_config --cflags --libs)


Run the compiled executable as follows:


./unsubscribe_program