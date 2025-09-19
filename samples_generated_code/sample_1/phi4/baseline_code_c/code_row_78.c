#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/evp.h>
#include <openssl/rand.h>
#include <mysql/mysql.h>

#define SALT_SIZE 16

void handle_error(const char *message) {
    perror(message);
    exit(EXIT_FAILURE);
}

int create_salt(unsigned char *salt, size_t salt_len) {
    if (!RAND_bytes(salt, salt_len)) {
        return -1;
    }
    return 0;
}

int hash_password(const char *password, const unsigned char *salt, unsigned char *hash) {
    EVP_MD_CTX *mdctx;
    const EVP_MD *alg = EVP_sha256();

    mdctx = EVP_MD_CTX_new();
    if (!mdctx) handle_error("EVP_MD_CTX_new failed");

    if (1 != EVP_DigestInit_ex(mdctx, alg, NULL)) handle_error("EVP_DigestInit_ex failed");
    if (1 != EVP_DigestUpdate(mdctx, password, strlen(password))) handle_error("EVP_DigestUpdate failed");
    if (1 != EVP_DigestUpdate(mdctx, salt, SALT_SIZE)) handle_error("EVP_DigestUpdate failed");
    if (1 != EVP_DigestFinal_ex(mdctx, hash, NULL)) handle_error("EVP_DigestFinal_ex failed");

    EVP_MD_CTX_free(mdctx);
    return 0;
}

int main() {
    const char *username;
    char password[256];
    unsigned char salt[SALT_SIZE];
    unsigned char hash[EVP_MAX_MD_SIZE];

    MYSQL *conn;
    MYSQL_STMT *stmt;

    // Generate salt
    if (create_salt(salt, SALT_SIZE) != 0) handle_error("Failed to create salt");

    // Read username and password from user
    printf("Enter username: ");
    scanf("%ms", &username);

    printf("Enter password: ");
    scanf("%255s", password);

    // Hash the password with the generated salt
    if (hash_password(password, salt, hash) != 0) handle_error("Failed to hash password");

    // Connect to database
    conn = mysql_init(NULL);
    if (!conn) handle_error("mysql_init() failed");
    if (mysql_real_connect(conn, "localhost", "root", "", "test_db", 3306, NULL, 0) == NULL)
        handle_error("mysql_real_connect() failed");

    // Prepare SQL statement
    const char *sql = "INSERT INTO users (username, password_hash, salt) VALUES (?, ?, ?)";
    stmt = mysql_stmt_init(conn);
    if (!stmt) handle_error("mysql_stmt_init() failed");
    if (mysql_stmt_prepare(stmt, sql, strlen(sql))) handle_error("mysql_stmt_prepare() failed");

    // Bind parameters
    MYSQL_BIND bind[3];
    memset(bind, 0, sizeof(bind));

    // Username
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;

    // Hashed password
    bind[1].buffer_type = MYSQL_TYPE_BLOB;
    bind[1].buffer = hash;
    bind[1].length = sizeof(hash);

    // Salt
    bind[2].buffer_type = MYSQL_TYPE_BLOB;
    bind[2].buffer = salt;
    bind[2].length = SALT_SIZE;

    if (mysql_stmt_bind_param(stmt, bind)) handle_error("mysql_stmt_bind_param() failed");

    // Execute statement
    if (mysql_stmt_execute(stmt)) handle_error("mysql_stmt_execute() failed");

    // Clean up
    mysql_stmt_close(stmt);
    mysql_close(conn);

    free(username);
    printf("User registered successfully.\n");
    
    return 0;
}