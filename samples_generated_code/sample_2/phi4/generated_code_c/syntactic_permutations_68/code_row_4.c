#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "base64.h"

#define BASE64_BUFFER_SIZE 8192

MYSQL* connect_to_db() {
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }
    return conn;
}

void upload_image(const char* image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    unsigned char buffer[file_size];
    fread(buffer, sizeof(unsigned char), file_size, file);

    fclose(file);

    char* base64_str = base64_encode(buffer, file_size);
    
    MYSQL *conn = connect_to_db();
    char query[1024];

    snprintf(query, sizeof(query),
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             basename(image_path), base64_str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    printf("Image uploaded successfully.\n");

    mysql_close(conn);
    free(base64_str);
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1]);

    return EXIT_SUCCESS;
}



// base64.h - header for base64 encoding functions

#ifndef BASE64_H
#define BASE64_H

char* base64_encode(const unsigned char *data, size_t input_length);

#endif // BASE64_H



// base64.c - implementation of base64 encoding functions

#include <string.h>
#include <stdlib.h>
#include "base64.h"

static const char encoding_table[] = 
    "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

char* base64_encode(const unsigned char *data, size_t input_length) {
    size_t output_size = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_size + 1);

    if (encoded_data == NULL) return NULL;

    for (int i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (int i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[output_size - 1 - i] = '=';

    encoded_data[output_size] = '\0';
    return encoded_data;
}

static const char mod_table[] = { 0, 2, 1 };