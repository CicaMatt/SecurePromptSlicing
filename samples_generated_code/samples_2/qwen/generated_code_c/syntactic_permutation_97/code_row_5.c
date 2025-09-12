#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "registration_db"

void hash_password(const char *password, char *output) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(output + (i * 2), "%02x", digest[i]);
    }
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[50], password[50], hashed_password[65], firstname[50], lastname[50], email[100];
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", firstname);
    printf("Enter Last Name: ");
    scanf("%49s", lastname);
    printf("Enter Email: ");
    scanf("%99s", email);

    hash_password(password, hashed_password);

    char query[500];
    snprintf(query, sizeof(query),
             "SELECT * FROM users WHERE username = '%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res && mysql_num_rows(res) > 0) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query),
                 "INSERT INTO users (username, password, firstname, lastname, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
                 username, hashed_password, firstname, lastname, email);
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
        } else {
            printf("Registration succeeded.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);

    return 0;
}