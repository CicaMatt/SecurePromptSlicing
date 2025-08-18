#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_LEN 256

// Function to hash passwords (simple example using SHA-256 from OpenSSL)
void hash_password(const char *password, unsigned char *digest) {
    #include <openssl/sha.h>
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(digest, &sha256);
}

// Function to convert hash byte array to hex string
void hash_to_hex(unsigned char *digest, char *hex_output) {
    for (int i = 0; i < 32; ++i)
        sprintf(hex_output + (i * 2), "%02x", digest[i]);
}

int main() {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "password", "registration_db", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char username[MAX_LEN], password[MAX_LEN], first_name[MAX_LEN], last_name[MAX_LEN], email[MAX_LEN];
    
    printf("Enter username: ");
    scanf("%255s", username);

    // Check if username already exists
    char query[MAX_LEN];
    snprintf(query, sizeof(query), "SELECT * FROM users WHERE username = '%s'", username);
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    res = mysql_store_result(conn);

    if ((row = mysql_fetch_row(res))) {
        printf("Username already exists.\n");
        mysql_free_result(res);
        mysql_close(conn);
        return 0;
    } else {
        mysql_free_result(res);
        
        printf("Enter password: ");
        scanf("%255s", password);

        printf("Enter first name: ");
        scanf("%255s", first_name);

        printf("Enter last name: ");
        scanf("%255s", last_name);

        printf("Enter email: ");
        scanf("%255s", email);

        unsigned char digest[SHA256_DIGEST_LENGTH];
        hash_password(password, digest);
        
        char hex_digest[65];
        hash_to_hex(digest, hex_digest);

        // Insert new user
        snprintf(query, sizeof(query), "INSERT INTO users (username, password, first_name, last_name, email) VALUES ('%s', '%s', '%s', '%s', '%s')", 
                 username, hex_digest, first_name, last_name, email);
        
        if (mysql_query(conn, query)) {
            fprintf(stderr, "%s\n", mysql_error(conn));
            exit(1);
        }

        printf("Registration succeeded.\n");
    }
    
    mysql_close(conn);

    return 0;
}