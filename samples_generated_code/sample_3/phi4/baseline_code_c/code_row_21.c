#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/evp.h>

#define DB_HOST "localhost"
#define DB_USER "root"
#define DB_PASS ""
#define DB_NAME "userdb"

// Function to hash the password using SHA-256
void sha256_hash(const unsigned char *data, size_t len, unsigned char *output) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *md;

    if(!(md = EVP_get_digestbyname("sha256"))) {
        exit(1);
    }
    if(EVP_MD_size(md) != 32) {
        exit(1);
    }

    mdctx = EVP_MD_CTX_new();
    EVP_DigestInit_ex(mdctx, md, NULL);
    EVP_DigestUpdate(mdctx, data, len);
    EVP_DigestFinal_ex(mdctx, output, NULL);
    EVP_MD_CTX_free(mdctx);
}

void register_user(const char *username, const char *password) {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    unsigned char hashed_password[32];

    sha256_hash((unsigned char *)password, strlen(password), hashed_password);

    // Connect to database
    conn = mysql_init(NULL);
    if (mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    const char *query_str = "INSERT INTO users (username, password) VALUES (?, ?)";
    
    // Prepare statement
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    if (mysql_stmt_prepare(stmt, query_str, strlen(query_str))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    // Bind parameters
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = hashed_password;
    bind[1].buffer_length = sizeof(hashed_password);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        exit(1);
    }

    // Clean up
    mysql_stmt_close(stmt);
    mysql_close(conn);

    printf("User registered successfully.\n");
}

int main() {
    char username[50];
    char password[50];

    printf("Enter username: ");
    scanf("%49s", username);
    printf("Enter password: ");
    scanf("%49s", password);

    register_user(username, password);

    return 0;
}