#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

void upload_image(FILE *image, char *name) {
    // Read image file into memory
    fseek(image, 0L, SEEK_END);
    int image_size = ftell(image);
    rewind(image);
    unsigned char *image_buffer = (unsigned char*)malloc(image_size);
    size_t bytes_read = fread(image_buffer, sizeof(unsigned char), image_size, image);
    
    // Convert image to base64 string
    int encoded_size = ((image_size / 3) * 4) + (image_size % 3 > 0 ? 4 : 0) + 1;
    unsigned char *encoded_buffer = (unsigned char*)malloc(encoded_size);
    base64_encode(image_buffer, image_size, encoded_buffer);
    
    // Insert image name and base64 string into database
    MYSQL mysql;
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "Error: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    char query[512];
    sprintf(query, "INSERT INTO images (name, data) VALUES ('%s', '%s');", name, encoded_buffer);
    if (mysql_query(&mysql, query)) {
        fprintf(stderr, "Error: %s\n", mysql_error(&mysql));
        exit(1);
    }
    
    free(image_buffer);
    free(encoded_buffer);
}