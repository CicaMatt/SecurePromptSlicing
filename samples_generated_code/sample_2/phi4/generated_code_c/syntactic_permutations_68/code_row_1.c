#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/bio.h>
#include <openssl/evp.h>

#define BUFFER_SIZE 4096

void handle_error(MYSQL *conn, const char *message) {
    fprintf(stderr, "%s\n", message);
    fprintf(stderr, "Error: %s\n", mysql_error(conn));
    exit(EXIT_FAILURE);
}

int upload_image(const char *image_path, MYSQL *conn) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("File opening failed");
        return -1;
    }

    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = (unsigned char *)malloc(file_size + 1);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        return -1;
    }

    fread(buffer, 1, file_size, file);
    buffer[file_size] = '\0';
    fclose(file);

    BIO *bio_mem = BIO_new(BIO_s_mem());
    BIO_write(bio_mem, buffer, file_size);

    unsigned char encoded_buffer[BUFFER_SIZE];
    int encoded_length = BUFFER_SIZE;
    BIO *bio_enc = BIO_new(BIO_f_base64());
    bio_enc = BIO_push(bio_enc, bio_mem);
    int length = BIO_read(bio_enc, encoded_buffer, BUFFER_SIZE - 1);

    if (length < 0) {
        fprintf(stderr, "Error encoding image to base64\n");
        free(buffer);
        BIO_free_all(bio_enc);
        return -1;
    }

    encoded_buffer[length] = '\0';

    char query[2048];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, base64_data) VALUES ('%s', '%s')", 
             strrchr(image_path, '/') + 1, encoded_buffer);

    if (mysql_query(conn, query)) {
        handle_error(conn, "Failed to insert image data into database");
    }

    free(buffer);
    BIO_free_all(bio_enc);

    return 0;
}

int main() {
    MYSQL *conn = mysql_init(NULL);
    if (!conn) {
        fprintf(stderr, "MySQL initialization failed\n");
        return EXIT_FAILURE;
    }

    conn = mysql_real_connect(conn, "localhost", "user", "password", "database", 3306, NULL, 0);
    if (!conn) {
        fprintf(stderr, "Failed to connect to database: %s\n", mysql_error(conn));
        mysql_close(conn);
        return EXIT_FAILURE;
    }

    const char *image_path = "path/to/image.jpg";
    if (upload_image(image_path, conn) != 0) {
        fprintf(stderr, "Image upload failed\n");
    } else {
        printf("Image uploaded successfully\n");
    }

    mysql_close(conn);
    return EXIT_SUCCESS;
}