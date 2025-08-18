#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define BUFFER_SIZE 1024

void upload_image(const char *image_path, const char *image_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    // Read the file into a buffer
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *buffer = (char *)malloc(filesize + 1);
    if (!buffer) {
        perror("Failed to allocate memory");
        fclose(file);
        return;
    }

    fread(buffer, 1, filesize, file);
    buffer[filesize] = '\0';
    fclose(file);

    // Convert image data to base64
    char base64_encoded[BUFFER_SIZE * 4 / 3 + 2];
    int encoded_length = 0;

    for (long i = 0; i < filesize; i += 3) {
        unsigned char triple[3] = { buffer[i], buffer[i+1], buffer[i+2] };
        unsigned char quad[4];

        quad[0] = (triple[0] & 0xfc) >> 2;
        quad[1] = ((triple[0] & 0x03) << 4) | ((triple[1] & 0xf0) >> 4);
        quad[2] = ((triple[1] & 0x0f) << 2) | ((triple[2] & 0xc0) >> 6);
        quad[3] = triple[2] & 0x3f;

        const char *base64_chars =
            "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
            "abcdefghijklmnopqrstuvwxyz"
            "0123456789+/";

        base64_encoded[encoded_length++] = base64_chars[quad[0]];
        base64_encoded[encoded_length++] = base64_chars[quad[1]];

        if (i + 1 < filesize) {
            base64_encoded[encoded_length++] = base64_chars[quad[2]];
        } else {
            base64_encoded[encoded_length++] = '=';
        }

        if (i + 2 < filesize) {
            base64_encoded[encoded_length++] = base64_chars[quad[3]];
        } else {
            base64_encoded[encoded_length++] = '=';
        }
    }

    base64_encoded[encoded_length] = '\0';

    // Insert image name and base64 string into the database
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(buffer);
        return;
    }

    char query[BUFFER_SIZE * 2];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             image_name, base64_encoded);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    mysql_close(conn);
    free(buffer);
}

int main() {
    upload_image("path/to/image.jpg", "image.jpg");
    return 0;
}