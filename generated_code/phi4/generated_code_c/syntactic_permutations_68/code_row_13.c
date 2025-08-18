#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUF_SIZE 1024

// Function declarations
void upload_image(const char *filename, const char *base64_string);

int main() {
    // Example usage
    upload_image("example.jpg", "iVBORw0KGgoAAAANSUhEUgAAAAUA");
    return 0;
}

void upload_image(const char *filename, const char *base64_string) {
    MYSQL conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize connection
    if (mysql_init(&conn) == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        exit(1);
    }

    // Connect to database
    if (!mysql_real_connect(&conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
        mysql_close(&conn);
        exit(1);
    }

    char query[BUF_SIZE];

    // Prepare SQL statement
    snprintf(query, BUF_SIZE, 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             filename, base64_string);

    // Execute SQL statement
    if (mysql_query(&conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(&conn));
    } else {
        printf("Image uploaded successfully.\n");
    }

    // Close connection
    mysql_close(&conn);
}


Make sure to replace `"localhost"`, `"user"`, `"password"`, and `"database"` with your actual MySQL server details. Also, ensure you have the `libmysqlclient` library linked during compilation by using `-lmysqlclient`.