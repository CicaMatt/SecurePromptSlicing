#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototypes
char* convert_image_to_base64(const char *image_path);
void upload_image(const char *image_name, const char *base64_string);

int main() {
    // Example usage of the function
    const char *image_name = "example.jpg";
    char *base64_string = convert_image_to_base64(image_name);
    
    if (base64_string) {
        upload_image(image_name, base64_string);
        free(base64_string);
    }
    
    return 0;
}

char* convert_image_to_base64(const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    // Dummy base64 conversion (replace with actual implementation)
    char *base64_string = (char*)malloc(file_size + 4); // Simplified estimation
    if (!base64_string) {
        perror("Failed to allocate memory");
        free(buffer);
        return NULL;
    }

    for (long i = 0; i < file_size; ++i) {
        sprintf(base64_string + (i / 3 * 4), "%c%c%c%c",
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[(buffer[i] >> 2)],
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[((buffer[i] & 0x03) << 4) | ((i + 1 < file_size) ? (buffer[i + 1] >> 4) : 0)],
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="[(((i + 1 < file_size) ? (buffer[i + 1] & 0x0f) : 0) << 2) | ((i + 2 < file_size) ? (buffer[i + 2] >> 6) : 0)],
                "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="[((i + 2 < file_size) ? buffer[i + 2] & 0x3f : '=')]);
    }

    base64_string[file_size / 3 * 4 + (file_size % 3 == 1 ? 2 : file_size % 3 == 2 ? 3 : 4)] = '\0';
    free(buffer);
    
    return base64_string;
}

void upload_image(const char *image_name, const char *base64_string) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    char query[256];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             image_name, base64_string);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully.\n");
    }

    // Close the connection
    mysql_close(conn);
}
