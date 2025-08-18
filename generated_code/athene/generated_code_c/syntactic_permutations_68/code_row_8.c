#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/pem.h>

void upload_image(const char *filename) {
    FILE *file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    fseek(file, 0, SEEK_END);
    long fsize = ftell(file);
    rewind(file);

    unsigned char *image_data = malloc(fsize + 1);
    fread(image_data, 1, fsize, file);
    fclose(file);

    BIO *b64 = BIO_new(BIO_f_base64());
    BIO_set_flags(b64, BIO_FLAGS_BASE64_NO_NL); //Ignore newlines
    BIO *bio = BIO_new(BIO_s_mem());
    bio = BIO_push(b64, bio);
    
    BIO_write(bio, image_data, fsize);
    BIO_flush(bio);

    long base64_length = BIO_get_mem_data(bio, &image_data);
    char *base64_string = malloc(base64_length + 1);
    memcpy(base64_string, (char *)image_data, base64_length);
    base64_string[base64_length] = '\0';

    BIO_free_all(bio);
    free(image_data);

    sqlite3 *db;
    int rc = sqlite3_open("images.db", &db);
    if (rc) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[1024];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s')", filename, base64_string);
    
    char *err_msg = 0;
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);
    if (rc != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
    } else {
        printf("Image uploaded successfully.\n");
    }

    free(base64_string);
    sqlite3_close(db);
}