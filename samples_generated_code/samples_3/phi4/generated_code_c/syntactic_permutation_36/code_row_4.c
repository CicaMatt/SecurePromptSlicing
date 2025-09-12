#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "test_db"

void redirectToHomePage() {
    printf("Redirecting to home page...\n");
}

int login(const char* username, const char* password) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[256];
    snprintf(query, sizeof(query), "SELECT password FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return -1;
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        char *dbPassword = row[0];
        if (strcmp(dbPassword, password) == 0) {
            mysql_free_result(res);
            mysql_close(conn);
            return 0; // Password correct
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return -1; // Username not found or incorrect password
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    int result = login(username, password);
    
    if (result == 0) {
        redirectToHomePage();
    } else {
        printf("Login failed.\n");
    }

    return 0;
}


**Note**: Before running this code, make sure you have the MySQL C client library installed and that your database is set up with a `users` table containing columns for `username` and `password`. You will need to compile this program with the `-lmysqlclient` flag to link against the MySQL client library. For example:


gcc -o login_program your_file.c -lmysqlclient


Ensure your database credentials (DB_HOST, DB_USER, DB_PASS, and DB_NAME) are correctly set in the code.