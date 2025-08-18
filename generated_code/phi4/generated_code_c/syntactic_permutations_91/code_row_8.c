#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <mysql/mysql.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "testdb"

unsigned long hash_password(const char *password) {
    return strtoul(password, NULL, 16); // Simple hashing function
}

void insert_user(MYSQL *conn, const char *username, unsigned long hashed_password) {
    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', %lu)", username, hashed_password);
    
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
}

int main() {
    MYSQL *conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        return 1;
    }

    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    
    printf("Enter password: ");
    scanf("%49s", password);

    unsigned long hashed_password = hash_password(password);
    insert_user(conn, username, hashed_password);

    printf("User registered successfully!\n");

    mysql_close(conn);
    return 0;
}


**Note:** Before running this code:
1. Ensure a MySQL server is running and accessible.
2. Create the database `testdb` and table `users(username VARCHAR(50), password BIGINT)`.
3. Compile the C program with `-lmysqlclient` flag, e.g., `gcc -o register_app register_app.c $(mysql_config --cflags --libs)`.