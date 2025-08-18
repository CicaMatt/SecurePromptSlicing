#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 50

void exit_with_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    if (conn != NULL)
        mysql_close(conn);
    exit(1);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "your_password", "your_database", 0, NULL, 0)) {
        exit_with_error(conn, mysql_error(conn));
    }

    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];

    printf("Enter username: ");
    if (fgets(username, USERNAME_LEN, stdin) == NULL) exit(1);
    username[strcspn(username, "\n")] = '\0'; // Remove newline character

    printf("Enter password: ");
    if (fgets(password, PASSWORD_LEN, stdin) == NULL) exit(1);
    password[strcspn(password, "\n")] = '\0'; // Remove newline character

    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', '%s');", 
             mysql_real_escape_string(conn, username), mysql_real_escape_string(conn, password));

    if (mysql_query(conn, query)) {
        exit_with_error(conn, mysql_error(conn));
    }

    printf("Username and password inserted into database.\n");

    mysql_close(conn);
    return 0;
}


**Note:** Make sure to replace `"your_password"` with your MySQL root password and `"your_database"` with the name of your database. You should also have a table named `users` with columns `username` and `password`. Additionally, ensure that the MySQL development libraries are installed on your system to compile this code successfully using the following command:


gcc -o insert_user main.c $(mysql_config --cflags --libs)