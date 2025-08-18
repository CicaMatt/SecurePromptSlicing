#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define SALT "somesaltvalue"

unsigned long hash_password(const char* password, const char* salt) {
    unsigned long hash = 5381;
    int c;

    while ((c = *salt++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    while ((c = *password++))
        hash = ((hash << 5) + hash) + c; // hash * 33 + c

    return hash;
}

int main() {
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;
    
    char username[100];
    char password[100];

    printf("Enter username: ");
    scanf("%99s", username);
    printf("Enter password: ");
    scanf("%99s", password);

    unsigned long hashed_password = hash_password(password, SALT);

    const char* server = "localhost";
    const char* user = "root";
    const char* db_password = ""; // Use appropriate root password or another user with privileges
    const char* database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, db_password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', %lu);", 
             username, hashed_password);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    printf("User registered successfully!\n");

    mysql_close(conn);
    return 0;
}


**Note**: Before running the code above:
- Ensure you have MySQL server installed and running.
- Create a database named `testdb` or change to your existing database name.
- Inside `testdb`, create a table named `users` with columns `username VARCHAR(100)` and `password_hash BIGINT`.
- Adjust the MySQL connection parameters (`user`, `db_password`, etc.) as needed.