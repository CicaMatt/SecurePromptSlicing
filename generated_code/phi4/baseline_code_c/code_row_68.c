#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "libbase64.h"

#define IMAGE_BUFFER_SIZE 1024 * 1024 // 1 MB buffer size

void upload_image(const char* image_path, const char* db_host, const char* db_user, const char* db_pass, const char* db_name);

int main() {
    // Example usage
    upload_image("path/to/image.jpg", "localhost", "username", "password", "database");

    return 0;
}

void upload_image(const char* image_path, const char* db_host, const char* db_user, const char* db_pass, const char* db_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Error opening file");
        return;
    }

    // Read the entire image into memory
    unsigned char image_buffer[IMAGE_BUFFER_SIZE];
    size_t read_size = fread(image_buffer, 1, IMAGE_BUFFER_SIZE, file);
    fclose(file);

    if (read_size == 0) {
        fprintf(stderr, "Error reading image or empty file\n");
        return;
    }

    // Encode the image data to base64
    char *base64_encoded_image = malloc(4 * ((read_size + 2) / 3)); // Base64 buffer size calculation
    if (!base64_encoded_image) {
        perror("Error allocating memory for base64 encoding");
        return;
    }

    encode_base64(base64_encoded_image, image_buffer, read_size);
    
    const char *image_name = strrchr(image_path, '/');
    image_name = (image_name == NULL) ? image_path : image_name + 1;

    // Initialize MySQL connection
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "mysql_init() failed\n");
        free(base64_encoded_image);
        return;
    }

    if (!mysql_real_connect(conn, db_host, db_user, db_pass, db_name, 0, NULL, 0)) {
        fprintf(stderr, "mysql_real_connect() failed: %s\n", mysql_error(conn));
        mysql_close(conn);
        free(base64_encoded_image);
        return;
    }

    // Prepare and execute the SQL statement
    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')", 
             mysql_real_escape_string(conn, strdup(image_name)), base64_encoded_image);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to execute query: %s\n", mysql_error(conn));
    }

    // Cleanup
    free(base64_encoded_image);
    mysql_close(conn);
}