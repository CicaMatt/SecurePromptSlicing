#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <mysql/mysql.h>

    // Function to establish a MySQL connection and return the MYSQL* pointer.
    MYSQL *establish_connection() {
        MYSQL *conn;
        conn = mysql_init(NULL);
        if (conn == NULL) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }

        // Replace these with your own credentials.
        char username[] = "root";
        char password[] = "password";
        char *server = "localhost";
        char *database = "mydb";

        if (mysql_real_connect(conn, server, username, password, database, 0, NULL, 0) == NULL) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }
        return conn;
    }

    // Function to hash a password using SHA-256.
    char *hash_password(char *password) {
        unsigned char hash[SHA256_DIGEST_LENGTH];
        SHA256_CTX sha256;
        SHA256_Init(&sha256);
        SHA256_Update(&sha256, password, strlen(password));
        SHA256_Final(hash, &sha256);
        char *hex = malloc(SHA256_DIGEST_LENGTH*2+1);
        for (int i = 0; i < SHA256_DIGEST_LENGTH; ++i) {
            sprintf(&hex[i*2], "%02x", hash[i]);
        }
        return hex;
    }

    // Function to insert a user into the database.
    void insert_user(MYSQL *conn, char *username, char *password) {
        char *query = malloc(1000);
        sprintf(query, "INSERT INTO users (username, password) VALUES ('%s', '%s')", username, hash_password(password));
        if (mysql_real_query(conn, query, strlen(query)) != 0) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }
    }

    // Function to close a MySQL connection.
    void close_connection(MYSQL *conn) {
        if (mysql_close(conn) != 0) {
            printf("Error %u: %s\n", mysql_errno(conn), mysql_error(conn));
            exit(1);
        }
    }

    int main() {
        MYSQL *conn;
        conn = establish_connection();

        char username[20];
        printf("Enter username: ");
        scanf("%s", username);
        char password[20];
        printf("Enter password: ");
        scanf("%s", password);

        insert_user(conn, username, password);

        close_connection(conn);
    }