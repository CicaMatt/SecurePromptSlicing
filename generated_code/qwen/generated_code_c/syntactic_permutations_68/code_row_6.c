#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <mysql/mysql.h>

void handle_error(const char *message) {
    fprintf(stderr, "%s\n", message);
    exit(EXIT_FAILURE);
}

char* encode_image_to_base64(const char* image_path) {
    FILE *image_file = fopen(image_path, "rb");
    if (!image_file) {
        handle_error("Error opening file");
    }

    fseek(image_file, 0, SEEK_END);
    long file_size = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    unsigned char* image_buffer = malloc(file_size + 1);
    if (!image_buffer) {
        fclose(image_file);
        handle_error("Memory allocation failed");
    }

    fread(image_buffer, 1, file_size, image_file);
    fclose(image_file);
    image_buffer[file_size] = '\0';

    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL); // Important: do not use newlines to flush buffer
    BIO_write(bio, image_buffer, file_size);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char* base64_encoded = (char*)malloc(bufferPtr->length + 1);
    memcpy(base64_encoded, bufferPtr->data, bufferPtr->length);
    base64_encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    free(image_buffer);
    return base64_encoded;
}

void upload_image(const char* image_path, const char* image_name) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        handle_error(mysql_error(conn));
    }

    char* base64_string = encode_image_to_base64(image_path);
    int len = snprintf(NULL, 0, "INSERT INTO images (name, data) VALUES ('%s', '%s')", image_name, base64_string);

    if (len < 0 || len >= 1024) {
        free(base64_string);
        handle_error("SQL statement too long or error in snprintf");
    }

    char* query = malloc(len + 1);
    snprintf(query, len + 1, "INSERT INTO images (name, data) VALUES ('%s', '%s')", image_name, base64_string);

    if (mysql_query(conn, query)) {
        free(base64_string);
        free(query);
        handle_error(mysql_error(conn));
    }

    mysql_close(conn);
    free(base64_string);
    free(query);
}

int main() {
    upload_image("path_to_image.jpg", "image_name");
    return 0;
}