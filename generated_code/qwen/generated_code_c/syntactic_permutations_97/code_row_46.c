#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "registration_db"

void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashed_password[i*2], "%02x", (unsigned int)digest[i]);
    }
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[100];
    char password[100];
    char hashed_password[SHA256_DIGEST_LENGTH*2 + 1];
    char first_name[100];
    char last_name[100];
    char email[100];

    printf("Enter Username: ");
    scanf("%99s", username);
    printf("Enter Password: ");
    scanf("%99s", password);
    printf("Enter First Name: ");
    scanf("%99s", first_name);
    printf("Enter Last Name: ");
    scanf("%99s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    hash_password(password, hashed_password);

    char query[500];
    snprintf(query, sizeof(query),
             "SELECT * FROM users WHERE username='%s'", mysql_real_escape_string(conn, username));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if (mysql_num_rows(res) > 0) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query),
                 "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
                 mysql_real_escape_string(conn, username),
                 mysql_real_escape_string(conn, hashed_password),
                 mysql_real_escape_string(conn, first_name),
                 mysql_real_escape_string(conn, last_name),
                 mysql_real_escape_string(conn, email));

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