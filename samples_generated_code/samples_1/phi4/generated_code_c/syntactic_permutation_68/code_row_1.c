#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

// Function to convert image to Base64 (dummy implementation for demonstration)
char* convert_image_to_base64(const char *image_path) {
    // Dummy base64 string, replace with actual conversion logic
    static char base64_str[] = "dGVzdCBiYXNlNjQgc3RyaW5n";
    return base64_str;
}

void upload_image(MYSQL *conn, const char *image_name, const char *image_path) {
    char query[BUFFER_SIZE];
    char *base64_string;

    // Convert image to Base64
    base64_string = convert_image_to_base64(image_path);

    // Prepare SQL query
    snprintf(query, BUFFER_SIZE, "INSERT INTO images (name, data) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, (char *)image_name),
             mysql_real_escape_string(conn, base64_string));

    // Execute query
    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }
}

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "host", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Example usage
    const char *image_name = "example.jpg";
    const char *image_path = "/path/to/example.jpg";

    upload_image(conn, image_name, image_path);

    mysql_close(conn);
    return 0;
}


Note: Replace `"host"`, `"user"`, `"password"`, and `"database"` with your actual MySQL server details. Also, implement the actual Base64 conversion logic in `convert_image_to_base64`.