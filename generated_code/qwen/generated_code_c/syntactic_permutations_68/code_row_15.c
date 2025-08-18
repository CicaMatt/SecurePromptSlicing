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

char* encode_base64(unsigned char *data, int length) {
    BIO *bio, *b64;
    BUF_MEM *bufferPtr;

    b64 = BIO_new(BIO_f_base64());
    bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);

    BIO_set_flags(bio, BIO_FLAGS_BASE64_NO_NL);
    BIO_write(bio, data, length);
    BIO_flush(bio);

    BIO_get_mem_ptr(bio, &bufferPtr);
    char *base64Encoded = (char *)malloc(bufferPtr->length + 1);
    memcpy(base64Encoded, bufferPtr->data, bufferPtr->length);
    base64Encoded[bufferPtr->length] = '\0';

    BIO_free_all(bio);

    return base64Encoded;
}

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) handle_error("Failed to open file");

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *fileData = (unsigned char *)malloc(fileSize + 1);
    fread(fileData, fileSize, 1, file);
    fclose(file);

    char *base64Encoded = encode_base64(fileData, fileSize);
    free(fileData);

    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "user", "password", "database_name", 0, NULL, 0)) {
        handle_error(mysql_error(conn));
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (image_data) VALUES ('%s')", base64Encoded);

    if (mysql_query(conn, query)) {
        handle_error(mysql_error(conn));
    }

    mysql_close(conn);
    free(base64Encoded);
}

int main() {
    upload_image("path_to_your_image.jpg");
    return 0;
}