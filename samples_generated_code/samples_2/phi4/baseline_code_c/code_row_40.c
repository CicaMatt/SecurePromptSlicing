#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "your_database_name"

void unsubscribe(const char *email) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    mysql_init(&conn);
    
    if (!mysql_real_connect(&conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT COUNT(*) FROM users WHERE email = '%s'", email);

    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        exit(1);
    }

    res = mysql_store_result(&conn);
    row = mysql_fetch_row(res);

    if (row && atoi(row[0]) > 0) {
        snprintf(query, sizeof(query), "DELETE FROM users WHERE email = '%s'", email);
        
        if (mysql_query(&conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(&conn));
        } else {
            printf("Email unsubscribed successfully.\n");
        }
    } else {
        printf("Email not found in the database.\n");
    }

    mysql_free_result(res);
    mysql_close(&conn);
}

int main() {
    char email[256];
    
    printf("Enter your email to unsubscribe: ");
    fgets(email, sizeof(email), stdin);
    email[strcspn(email, "\n")] = '\0'; // Remove newline character

    unsubscribe(email);

    return 0;
}


Make sure you replace `"your_database_name"` with the actual name of your database and configure `SERVER`, `USER`, and `PASSWORD` as needed for your MySQL setup. You will also need to have the MySQL C API installed, which is typically done via a package like `libmysqlclient-dev`.