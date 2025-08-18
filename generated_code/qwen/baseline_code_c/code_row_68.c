#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define MAX_FILENAME_LEN 256
#define MAX_BASE64_LEN 1024 * 1024 // Assuming image is less than 1MB

void upload_image(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char* buffer = (unsigned char*)malloc(file_size + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    // Calculate the size of the base64 encoded string
    int base64_len = ((file_size + 2) / 3) * 4;

    char* base64_string = (char*)malloc(base64_len + 1);
    if (!base64_string) {
        perror("Failed to allocate memory for base64 string");
        free(buffer);
        return;
    }

    // Base64 encode the file content
    const unsigned char b64_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i, j;
    for (i = 0, j = 0; i < file_size;) {
        unsigned int octet_a = i < file_size ? buffer[i++] : 0;
        unsigned int octet_b = i < file_size ? buffer[i++] : 0;
        unsigned int octet_c = i < file_size ? buffer[i++] : 0;

        unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        base64_string[j++] = b64_table[(triple >> 3 * 6) & 0x3F];
        base64_string[j++] = b64_table[(triple >> 2 * 6) & 0x3F];
        base64_string[j++] = i - file_size >= 1 ? '=' : b64_table[(triple >> 1 * 6) & 0x3F];
        base64_string[j++] = i - file_size >= 2 ? '=' : b64_table[(triple >> 0 * 6) & 0x3F];
    }
    base64_string[base64_len] = '\0';

    // Insert into database
    MYSQL* conn;
    MYSQL_RES* res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buffer);
        free(base64_string);
        return;
    }

    char query[MAX_BASE64_LEN + MAX_FILENAME_LEN + 128];
    snprintf(query, sizeof(query), "INSERT INTO images (filename, base64_data) VALUES ('%s', '%s')", filename, base64_string);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully.\n");
    }

    mysql_close(conn);
    free(buffer);
    free(base64_string);
}

int main() {
    upload_image("example.jpg");
    return 0;
}