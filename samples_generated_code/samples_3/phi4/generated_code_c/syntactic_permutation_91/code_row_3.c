#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
    #include <windows.h>
#else
    #include <unistd.h>
#endif

#include <mysql/mysql.h>
#include <openssl/sha.h>

#define SERVER "localhost"
#define USER "root"
#define PASSWORD "your_password"
#define DATABASE "test_db"

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_ROW row;
    MYSQL_RES *res;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, SERVER, USER, PASSWORD, DATABASE, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[100];
    char password[100];

    printf("Enter Username: ");
    scanf("%99s", username);

    printf("Enter Password: ");
    scanf("%99s", password);

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    hash_password(password, hashed_password);

    char query[256];
    sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')",
            username,
            mysql_real_escape_string(conn, (char *)hashed_password));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("User added successfully!\n");

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}


Note: Before running this code, make sure to replace `"your_password"` with your actual MySQL root password. Also, ensure the database `test_db` and table `users` (with columns `username` and `password`) exist in your MySQL server. You need to have OpenSSL library installed for SHA256 hashing and MySQL client library linked during compilation:


gcc -o web_app main.c -lmysqlclient -lcrypto


This example uses SHA-256 for password hashing via the OpenSSL library, which is a basic form of security and should be enhanced for real-world applications.