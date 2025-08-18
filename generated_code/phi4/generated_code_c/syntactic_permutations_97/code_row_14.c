#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "test_db"

void hash_password(const char *password, unsigned char outputBuffer[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(outputBuffer, &sha256);
}

int main() {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[50], password[50], first_name[50];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%49s", username);

    printf("Enter password: ");
    scanf("%49s", password);

    printf("Enter first name: ");
    scanf("%49s", first_name);

    hash_password(password, hashed_password);
    
    mysql_init(&conn);
    if (!mysql_real_connect(&conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return EXIT_FAILURE;
    }

    char query[256];
    sprintf(query, "SELECT * FROM users WHERE username = '%s'", username);
    
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        return EXIT_FAILURE;
    }

    res = mysql_store_result(&conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Username already exists.\n");
    } else {
        char insertQuery[512];
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            sprintf(insertQuery + strlen(insertQuery), "%02x", hashed_password[i]);
        }
        
        sprintf(query, "INSERT INTO users(username, password_hash, first_name) VALUES('%s', '%s', '%s')",
                username, insertQuery, first_name);
                
        if (mysql_query(&conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(&conn));
        } else {
            printf("Registration succeeded.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(&conn);

    return 0;
}