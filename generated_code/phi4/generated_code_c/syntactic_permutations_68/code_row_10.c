#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototypes
char* read_image_to_base64(const char *filename);
void upload_image(MYSQL *conn, const char *name, const char *base64_str);

int main() {
    // Initialize MySQL connection
    MYSQL *conn = mysql_init(NULL);
    
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Simulate user uploading an image
    const char *image_filename = "path/to/image.jpg";
    const char *image_name = "uploaded_image";

    char *base64_str = read_image_to_base64(image_filename);

    if (base64_str != NULL) {
        upload_image(conn, image_name, base64_str);
        free(base64_str);
    }

    mysql_close(conn);
    return 0;
}

char* read_image_to_base64(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    rewind(file);

    // Allocate memory for reading the entire file
    unsigned char *buffer = (unsigned char *)malloc(filesize);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, filesize, file);
    fclose(file);

    // Convert binary data to base64 (simple implementation)
    size_t b64_len = 4 * ((filesize + 2) / 3); // Base64 length
    char *base64_str = (char *)malloc(b64_len + 1); // +1 for null terminator

    if (!base64_str) {
        perror("Failed to allocate memory");
        free(buffer);
        return NULL;
    }

    const char base64_chars[] =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    int i, j;
    unsigned char temp[3], encoded[4];
    for (i = 0, j = 0; i < filesize;) {
        memset(temp, 0, sizeof(temp));
        for (size_t k = 0; k < 3 && i < filesize; ++k) {
            temp[k] = buffer[i++];
        }

        encoded[0] = base64_chars[(temp[0] & 0xFC) >> 2];
        encoded[1] = base64_chars[((temp[0] & 0x03) << 4) | ((temp[1] & 0xF0) >> 4)];
        encoded[2] = (i > filesize) ? '=' : base64_chars[((temp[1] & 0x0F) << 2) | ((temp[2] & 0xC0) >> 6)];
        encoded[3] = (i > filesize + 1) ? '=' : base64_chars[temp[2] & 0x3F];

        for (size_t k = 0; k < 4; ++k) {
            base64_str[j++] = encoded[k];
        }
    }

    base64_str[j] = '\0';

    free(buffer);
    return base64_str;
}

void upload_image(MYSQL *conn, const char *name, const char *base64_str) {
    // Prepare SQL statement
    if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS images (id INT AUTO_INCREMENT PRIMARY KEY, name VARCHAR(255), image_base64 TEXT)")) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return;
    }

    char query[1024];
    snprintf(query, sizeof(query),
             "INSERT INTO images (name, image_base64) VALUES ('%s', '%s')",
             name,
             base64_str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully.\n");
    }
}