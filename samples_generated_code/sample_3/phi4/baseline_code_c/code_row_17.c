#include <stdio.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/sha.h>

void hash_password(const char *password, unsigned char output[SHA256_DIGEST_LENGTH]) {
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, password, strlen(password));
    SHA256_Final(output, &sha256);
}

int main() {
    MYSQL *conn;
    MYSQL_STMT *stmt;
    const char *server = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *database = "testdb";

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return 1;
    }

    char username[256];
    char input_password[256];
    unsigned char hashed_password[SHA256_DIGEST_LENGTH];

    printf("Enter username: ");
    scanf("%255s", username);
    printf("Enter password: ");
    scanf("%255s", input_password);

    hash_password(input_password, hashed_password);

    const char *insert_query = "INSERT INTO users (username, password) VALUES (?, ?)";
    stmt = mysql_stmt_init(conn);

    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        return 1;
    }

    if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed\n");
        return 1;
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].length = strlen(username);

    char hex_password[SHA256_DIGEST_LENGTH * 2 + 1];
    for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
        sprintf(hex_password + (i * 2), "%02x", hashed_password[i]);
    }

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = hex_password;
    bind[1].length = strlen(hex_password);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed\n");
        return 1;
    }

    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed\n");
        return 1;
    }

    printf("User added successfully.\n");

    mysql_stmt_close(stmt);
    mysql_close(conn);

    return 0;
}