#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD ""
#define DATABASE "testdb"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int connect_db() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }
    return conn;
}

void register_user(const char *username, const char *password) {
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    MYSQL *conn = connect_db();
    if (conn == NULL) {
        exit(EXIT_FAILURE);
    }

    char query[512];
    snprintf(query, sizeof(query), "INSERT INTO users(username, password) VALUES('%s', '%s')",
             username,
             mysql_real_escape_string(conn, (char *)hashed_password, SHA256_DIGEST_LENGTH));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    printf("User registered successfully.\n");
    mysql_close(conn);
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}


To compile and run this code:

1. Install MySQL server and client libraries.
2. Install OpenSSL library.
3. Create a database named `testdb` and a table named `users` with columns `username` (VARCHAR) and `password` (BINARY(32)).
4. Compile the program using:
   
   gcc -o register_app register_app.c $(mysql_config --cflags --libs) -lssl -lcrypto
   
5. Run the compiled executable:
   
   ./register_app