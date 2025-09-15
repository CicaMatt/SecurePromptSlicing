#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

#define USERNAME_LEN 50
#define PASSWORD_LEN 64

void hash_password(const char *password, unsigned char hashed_password[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashed_password, &sha256);
}

int main() {
    MYSQL conn;
    const char *server = "localhost";
    const char *user = "root";
    const char *password = ""; // Use your MySQL root password
    const char *database = "test_db"; // Use your database name

    char username[USERNAME_LEN];
    char input_password[PASSWORD_LEN];

    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "Failed to initialize MySQL: %s\n", mysql_error(&conn));
        return 1;
    }

    if (!mysql_real_connect(&conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "Connection failed: %s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 1;
    }

    printf("Enter username: ");
    fgets(username, USERNAME_LEN, stdin);
    username[strcspn(username, "\n")] = '\0';

    printf("Enter password: ");
    fgets(input_password, PASSWORD_LEN, stdin);
    input_password[strcspn(input_password, "\n")] = '\0';

    hash_password(input_password, hashed_password);

    stmt = mysql_stmt_init(&conn);
    if (!stmt) {
        fprintf(stderr, "Failed to initialize statement handler\n");
        mysql_close(&conn);
        return 1;
    }

    const char *query = "INSERT INTO users (username, password) VALUES (?, ?)";
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Prepare failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&conn);
        return 1;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = hashed_password;
    bind[1].buffer_length = SHA256_DIGEST_LENGTH;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "Bind failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&conn);
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "Execute failed: %s\n", mysql_stmt_error(stmt));
        mysql_stmt_close(stmt);
        mysql_close(&conn);
        return 1;
    }

    printf("User registered successfully!\n");

    mysql_stmt_close(stmt);
    mysql_close(&conn);

    return 0;
}
