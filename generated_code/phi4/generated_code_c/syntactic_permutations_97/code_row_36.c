#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "registration_db"

void handle_error(MYSQL *conn, const char *msg) {
    fprintf(stderr, "%s\n", msg);
    fprintf(stderr, "Error: %s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
}

unsigned char* hash_password(const unsigned char *password, size_t length) {
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, length);
    SHA256_Final(hash, &sha256);

    unsigned char* hashed_password = malloc(SHA256_DIGEST_LENGTH * sizeof(unsigned char));
    if (!hashed_password) {
        perror("Failed to allocate memory for hash");
        exit(EXIT_FAILURE);
    }
    memcpy(hashed_password, hash, SHA256_DIGEST_LENGTH);
    return hashed_password;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0)) {
        handle_error(conn, "mysql_real_connect() failed");
    }

    char username[50], password[50], first_name[50], last_name[50], email[100];
    
    printf("Enter Username: ");
    scanf("%49s", username);
    printf("Enter Password: ");
    scanf("%49s", password);
    printf("Enter First Name: ");
    scanf("%49s", first_name);
    printf("Enter Last Name: ");
    scanf("%49s", last_name);
    printf("Enter Email: ");
    scanf("%99s", email);

    unsigned char* hashed_password = hash_password((unsigned char*)password, strlen(password));

    char query[256];
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username='%s'", username);
    if (mysql_query(conn, query)) {
        handle_error(conn, "Failed to check existing user");
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        handle_error(conn, "Failed to retrieve result set");
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    mysql_free_result(result);

    if (count > 0) {
        printf("Username already exists.\n");
    } else {
        sprintf(query, 
            "INSERT INTO users (username, password, first_name, last_name, email) VALUES "
            "('%s', '%s', '%s', '%s', '%s')",
            username,
            hashed_password,
            first_name,
            last_name,
            email);

        if (mysql_query(conn, query)) {
            handle_error(conn, "Failed to insert new user");
        } else {
            printf("Registration succeeded.\n");
        }
    }

    free(hashed_password);
    mysql_close(conn);
    return 0;
}
