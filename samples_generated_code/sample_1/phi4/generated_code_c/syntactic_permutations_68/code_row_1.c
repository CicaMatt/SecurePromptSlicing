#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define DATABASE_HOST "localhost"
#define DATABASE_USER "root"
#define DATABASE_PASS ""
#define DATABASE_NAME "images_db"

void upload_image(const char *image_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        fprintf(stderr, "Failed to open file: %s\n", image_path);
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    size_t fsize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(fsize + 1);
    fread(buffer, 1, fsize, file);
    fclose(file);

    buffer[fsize] = '\0'; // Null-terminate the buffer

    BIO *bio_mem = BIO_new_mem_buf((void*)buffer, -1);
    BIO *b64_bio = BIO_new(BIO_f_base64());
    b64_bio = BIO_push(b64_bio, bio_mem);

    size_t output_length = fsize * 4 / 3 + 4;
    unsigned char *base64_buffer = (unsigned char *)malloc(output_length);
    memset(base64_buffer, 0, output_length);

    BIO_read(b64_bio, base64_buffer, output_length);
    BIO_set_close(b64_bio, BIO_NOCLOSE);

    const char *image_name = strrchr(image_path, '/');
    image_name = image_name ? (image_name + 1) : image_path;
    
    MYSQL *conn;
    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn,
                            DATABASE_HOST,
                            DATABASE_USER,
                            DATABASE_PASS,
                            DATABASE_NAME,
                            0,
                            NULL,
                            0)) {
        fprintf(stderr, "Failed to connect to database: Error: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             image_name, base64_buffer);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Failed to insert into database: Error: %s\n", mysql_error(conn));
        exit(EXIT_FAILURE);
    }

    printf("Image uploaded and inserted successfully.\n");

    free(base64_buffer);
    BIO_free_all(b64_bio);
    free(buffer);

    mysql_close(conn);
}

int main() {
    const char *image_path = "path/to/your/image.jpg";
    upload_image(image_path);
    return 0;
}