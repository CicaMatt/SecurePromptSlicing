#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define DB_HOST "localhost"
#define DB_USER "your_username"
#define DB_PASS "your_password"
#define DB_NAME "your_database"

void hashPassword(const char *password, unsigned char hashed[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed, &sha256);
}

int connectToDatabase(MYSQL **con) {
    *con = mysql_init(NULL);
    if (*con == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }
    if (mysql_real_connect(*con, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(*con));
        return 1;
    }
    return 0;
}

int usernameExists(MYSQL *con, const char *username) {
    char query[256];
    snprintf(query, sizeof(query), "SELECT id FROM users WHERE username = '%s'", username);
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return -1;
    }

    MYSQL_RES *result = mysql_store_result(con);
    int exists = (result && mysql_num_rows(result) > 0);
    if (result) {
        mysql_free_result(result);
    }
    
    return exists;
}

int registerUser(MYSQL *con, const char *username, unsigned char hashedPassword[SHA256_DIGEST_LENGTH]) {
    char query[512];
    snprintf(query, sizeof(query), 
             "INSERT INTO users (username, password_hash) VALUES ('%s', '%s')",
             username,
             mysql_real_escape_string(con, (char *)hashedPassword));
    
    if (mysql_query(con, query)) {
        fprintf(stderr, "%s\n", mysql_error(con));
        return 1;
    }

    return 0;
}

int main() {
    MYSQL *con = NULL;

    if (connectToDatabase(&con)) {
        return EXIT_FAILURE;
    }

    char username[50], password[50];
    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    if (usernameExists(con, username) == 1) {
        fprintf(stderr, "Username already exists.\n");
        mysql_close(con);
        return EXIT_FAILURE;
    }

    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    hashPassword(password, hashedPassword);

    if (registerUser(con, username, hashedPassword)) {
        fprintf(stderr, "Registration failed.\n");
        mysql_close(con);
        return EXIT_FAILURE;
    } else {
        printf("Registration succeeded.\n");
    }

    mysql_close(con);
    return EXIT_SUCCESS;
}