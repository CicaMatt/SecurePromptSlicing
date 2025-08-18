#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define PASSWORD_HASH_LENGTH 41 // SHA-1 produces a 40-character hash + 1 for null terminator

// Function to simulate hashing (using MD5 for simplicity in this example)
void hash_password(const char *password, char *hashed_password) {
    unsigned char digest[16]; // MD5 produces a 128-bit digest
    char *md5_string;

    MD5((unsigned char*)password, strlen(password), (unsigned char*)&digest); 
    md5_string = (char *) malloc(33);
    for(int i = 0; i < 16; ++i)
        sprintf(&md5_string[i*2], "%02x", (unsigned int)digest[i]);
    
    strcpy(hashed_password, md5_string);
    free(md5_string);
}

int main() {
    MYSQL *conn;
    char username[256];
    char password[256];
    char hashed_password[PASSWORD_HASH_LENGTH];

    // Initialize the connection
    conn = mysql_init(NULL);

    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return EXIT_FAILURE;
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "root", "", "your_database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("Enter username: ");
    scanf("%255s", username);

    printf("Enter password: ");
    scanf("%255s", password);

    // Hash the password
    hash_password(password, hashed_password);

    // Prepare an SQL statement for inserting data into the database
    MYSQL_STMT *stmt;
    const char *insert_query = "INSERT INTO users (username, password) VALUES (?, ?)";
    
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "mysql_stmt_init() failed\n");
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    if (mysql_stmt_prepare(stmt, insert_query, strlen(insert_query))) {
        fprintf(stderr, "mysql_stmt_prepare() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    // Bind the username parameter
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)username;
    bind[0].buffer_length = strlen(username);

    // Bind the hashed password parameter
    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = (char *)hashed_password;
    bind[1].buffer_length = strlen(hashed_password);

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "mysql_stmt_bind_param() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    // Execute the statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "mysql_stmt_execute() failed: %s\n", mysql_stmt_error(stmt));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    printf("User registered successfully.\n");

    // Close the connection and clean up
    mysql_stmt_close(stmt);
    mysql_close(conn);

    return 0;
}