#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "base64.h"  // Assume you have a header for Base64 encoding functions

#define BUFFER_SIZE 4096

void upload_image(const char *filename, MYSQL *conn) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0L, SEEK_END);
    size_t fsize = ftell(file);
    rewind(file);

    unsigned char *buffer = (unsigned char *)malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    buffer[fsize] = '\0';

    fclose(file);

    // Convert to Base64
    int encoded_size = base64_enc_len(fsize);
    char *encoded_data = malloc(encoded_size);
    base64_encode(encoded_data, (char *)buffer, fsize);

    free(buffer);

    const char *sql = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)";
    char query[BUFFER_SIZE + encoded_size];

    snprintf(query, sizeof(query), sql, filename, encoded_data);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    free(encoded_data);
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }

    if (mysql_real_connect(conn, "localhost", "user", "password",
                           "database", 0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    upload_image("example.jpg", conn);

    mysql_close(conn);
    return 0;
}