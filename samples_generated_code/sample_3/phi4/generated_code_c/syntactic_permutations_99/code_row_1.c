#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "testdb"

unsigned long hash_password(const char *password) {
    unsigned long hashed = 5381;
    int c;

    while ((c = *password++))
        hashed = (((hashed << 5) + hashed) + c) % 4294967296UL;

    return hashed;
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    char username[50], password[50];
    unsigned long hashed_password;
    
    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    hashed_password = hash_password(password);

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[200];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', %lu)", username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);
    
    return 0;
}


Note: Make sure that the MySQL server is installed and running on your local machine. Also, ensure you have created a database named `testdb` and a table named `users` with columns `username` (VARCHAR) and `password` (UNSIGNED LONG). Adjust the server, user, password, and database variables as needed for your setup.