#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "registration_db"

void hash_password(const char *password, unsigned char hash[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hash, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    char username[100];
    char password[100];
    char firstName[100];
    char lastName[100];
    char email[100];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);
    printf("Enter First Name: ");
    scanf("%s", firstName);
    printf("Enter Last Name: ");
    scanf("%s", lastName);
    printf("Enter Email: ");
    scanf("%s", email);

    hash_password(password, hashed_password);

    char hashed_password_str[(SHA256_DIGEST_LENGTH * 2) + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i)
        sprintf(&hashed_password_str[i*2], "%02x", (unsigned int)hashed_password[i]);

    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        exit(1);
    }

    char query[500];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username='%s'", username);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Error querying database: %s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    res = mysql_store_result(conn);
    if (res && mysql_num_rows(res) > 0) {
        printf("Username already exists.\n");
    } else {
        snprintf(query, sizeof(query),
                 "INSERT INTO users (username, password, first_name, last_name, email) "
                 "VALUES ('%s', '%s', '%s', '%s', '%s')",
                 username, hashed_password_str, firstName, lastName, email);

        if (mysql_query(conn, query)) {
            fprintf(stderr, "Error inserting into database: %s\n", mysql_error(conn));
        } else {
            printf("Registration succeeded.\n");
        }
    }

    mysql_free_result(res);
    mysql_close(conn);
    return 0;
}