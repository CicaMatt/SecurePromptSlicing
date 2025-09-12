#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Include OpenSSL library for hashing
#include <openssl/sha.h>
#include <mysql/mysql.h> // MySQL connector/c client library

#define USERNAME_LEN 50
#define PASSWORD_LEN 128

void hash_password(const char *password, unsigned char hashedPassword[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(hashedPassword, &sha256);
}

int main() {
    MYSQL conn;
    MYSQL_STMT *stmt;
    
    char username[USERNAME_LEN];
    char password[PASSWORD_LEN];
    unsigned char hashedPassword[SHA256_DIGEST_LENGTH];
    
    // Prompt the user for input
    printf("Enter username: ");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = '\0'; // Remove newline

    printf("Enter password: ");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = '\0';

    // Hash the password
    hash_password(password, hashedPassword);

    // Initialize MySQL connection
    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }

    if (!mysql_real_connect(&conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        return 1;
    }
    
    // Prepare SQL statement
    stmt = mysql_stmt_init(&conn);
    if (!stmt) {
        fprintf(stderr, "MySQL statement initialization failed\n");
        mysql_close(&conn);
        return 1;
    }

    const char *query = "INSERT INTO users (username, password_hash) VALUES (?, ?)";
    
    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        mysql_close(&conn);
        return 1;
    }
    
    // Bind parameters
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    char hashedPasswordStr[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(&hashedPasswordStr[i*2], "%02x", hashedPassword[i]);
    }

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hashedPasswordStr;
    bind[1].buffer_length = sizeof(hashedPasswordStr) - 1;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        mysql_close(&conn);
        return 1;
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
    } else {
        printf("User inserted successfully.\n");
    }

    // Cleanup
    mysql_stmt_close(stmt);
    mysql_close(&conn);

    return 0;
}