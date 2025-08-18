#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define BUFFER_SIZE 256

void hash_password(const char *password, unsigned char *result) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(result, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[BUFFER_SIZE];
    char password[BUFFER_SIZE];
    char first_name[BUFFER_SIZE];
    char last_name[BUFFER_SIZE];
    char email[BUFFER_SIZE];

    unsigned char hashed_password[SHA256_DIGEST_LENGTH];
    
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "root", "password", "your_database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", password);
    printf("Enter first name: ");
    scanf("%255s", first_name);
    printf("Enter last name: ");
    scanf("%255s", last_name);
    printf("Enter email: ");
    scanf("%255s", email);

    hash_password(password, hashed_password);

    char query[BUFFER_SIZE * 2];
    snprintf(query, sizeof(query), "SELECT username FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    res = mysql_store_result(conn);
    
    if ((row = mysql_fetch_row(res))) {
        printf("Username already exists.\n");
    } else {
        char insert_query[BUFFER_SIZE * 2];
        snprintf(insert_query, sizeof(insert_query), 
                 "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
                 username,
                 mysql_hex_string(conn, hashed_password),
                 first_name,
                 last_name,
                 email);

        if (mysql_query(conn, insert_query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Registration successful.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return EXIT_SUCCESS;
}