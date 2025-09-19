#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <openssl/sha.h>

#include <mysql/mysql.h>

#define BUFFER_SIZE 256

void hash_password(const char *input, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, input, strlen(input));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;
    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Update with your MySQL password
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char username[BUFFER_SIZE];
    char passwdbuf[BUFFER_SIZE];
    unsigned char hash[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", passwdbuf);

    hash_password(passwdbuf, hash);

    char hashed_pass[BUFFER_SIZE * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hashed_pass + (i * 2), "%02x", hash[i]);
    }

    char query[BUFFER_SIZE * 3] = "INSERT INTO users (username, password) VALUES ('%s', '%s');";
    snprintf(query, sizeof(query), query, username, hashed_pass);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    printf("User inserted successfully.\n");

    mysql_close(conn);
    return 0;
}


Ensure that you have the OpenSSL library and MySQL client library installed on your system to compile this program. You can compile it using a command similar to:


gcc -o user_insert user_insert.c $(mysql_config --cflags --libs) -lssl -lcrypto