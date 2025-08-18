#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql.h>
#include <openssl/sha.h>

#define MAX_USERNAME 50
#define MAX_PASSWORD 100
#define MAX_NAME 50
#define MAX_EMAIL 100

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

    char username[MAX_USERNAME];
    char password[MAX_PASSWORD];
    char hashed_password[SHA256_DIGEST_LENGTH*2 + 1];
    char first_name[MAX_NAME];
    char last_name[MAX_NAME];
    char email[MAX_EMAIL];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", first_name);
    printf("Enter Last Name: ");
    scanf("%s", last_name);
    printf("Enter Email: ");
    scanf("%s", email);

    hash_password(password, hashed_password);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "your_db_user", "your_db_password", "your_database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if (mysql_num_rows(res) > 0) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", username, hashed_password, first_name, last_name, email);

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