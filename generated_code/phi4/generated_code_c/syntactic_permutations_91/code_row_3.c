#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 64

void hash_password(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256((unsigned char *)password, strlen(password), hashed);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "webapp";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    unsigned char hashed_password[PASSWORD_LEN];
    
    printf("Enter username: ");
    char username[USERNAME_LEN];
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    char password_input[PASSWORD_LEN];
    fgets(password_input, PASSWORD_LEN, stdin);
    password_input[strcspn(password_input, "\n")] = '\0';

    hash_password(password_input, hashed_password);

    unsigned long hashed_len = SHA256_DIGEST_LENGTH;
    
    char query[256];
    snprintf(query, sizeof(query), "INSERT INTO users (username, password) VALUES ('%s', %s)",
             username, mysql_real_escape_string(conn, (char *)hashed_password));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User registered successfully.\n");

    mysql_close(conn);
    return 0;
}


Make sure to:

1. Have MySQL server running and a database named `webapp` with a table `users`.
2. Table `users` should have columns: `username VARCHAR(50)` and `password BINARY(32)`.
3. Install the necessary libraries (`mysqlclient`, OpenSSL).
4. Compile the program using:
   
   gcc -o register_app your_file.c -lmysqlclient -lcrypto