#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define HASH_LENGTH 32

void handle_error(MYSQL *conn) {
    fprintf(stderr, "%s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
}

char* hash_password(const char* password) {
    unsigned char hash[HASH_LENGTH];
    unsigned int length;
    
    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    if (!mdctx) return NULL;

    if (1 != EVP_DigestInit_ex(mdctx, EVP_sha256(), NULL)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }

    if (1 != EVP_DigestFinal_ex(mdctx, hash, &length)) {
        EVP_MD_CTX_free(mdctx);
        return NULL;
    }
    
    EVP_MD_CTX_free(mdctx);

    char* hashed_password = malloc(HASH_LENGTH + 1);
    for (unsigned int i = 0; i < HASH_LENGTH; i++) {
        sprintf(hashed_password + (i * 2), "%02x", hash[i]);
    }

    return hashed_password;
}

int main() {
    MYSQL *conn;

    conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(EXIT_FAILURE);
    }

    if (!mysql_real_connect(conn, "localhost", "root", "", "registration_db", 0, NULL, 0)) {
        handle_error(conn);
    }
    
    char username[256], password[256], first_name[256], last_name[256], email[256];
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

    char query[1024];
    
    sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", mysql_real_escape_string(conn, username));
    if (mysql_query(conn, query)) {
        handle_error(conn);
    }

    MYSQL_RES *result = mysql_store_result(conn);
    if (!result) {
        handle_error(conn);
    }

    MYSQL_ROW row = mysql_fetch_row(result);
    int count = atoi(row[0]);
    
    mysql_free_result(result);

    if (count > 0) {
        printf("Username already exists.\n");
    } else {
        char *hashed_password = hash_password(password);
        
        sprintf(query, "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')",
                mysql_real_escape_string(conn, username),
                hashed_password ? mysql_real_escape_string(conn, hashed_password) : "",
                mysql_real_escape_string(conn, first_name),
                mysql_real_escape_string(conn, last_name),
                mysql_real_escape_string(conn, email));
        
        if (mysql_query(conn, query)) {
            handle_error(conn);
        }

        printf("Registration succeeded.\n");

        free(hashed_password);
    }
    
    mysql_close(conn);

    return 0;
}


Make sure to have the MySQL server running and a database named `registration_db` with a table `users` structured as follows before you compile and run this code:


CREATE DATABASE registration_db;

USE registration_db;

CREATE TABLE users (
    id INT AUTO_INCREMENT PRIMARY KEY,
    username VARCHAR(255) UNIQUE NOT NULL,
    password CHAR(64) NOT NULL,
    first_name VARCHAR(255),
    last_name VARCHAR(255),
    email VARCHAR(255)
);


Also, ensure you have MySQL C connector and OpenSSL libraries installed to link during compilation. Compile with:


gcc -o registration registration.c $(mysql_config --cflags --libs) -lssl -lcrypto