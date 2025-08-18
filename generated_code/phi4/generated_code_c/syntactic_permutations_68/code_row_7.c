#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <openssl/bio.h>
#include <openssl/evp.h>
#include <openssl/buffer.h>

#define BUF_SIZE 1024

void upload_image(const char *image_path, const char *image_name, MYSQL *conn);

int main() {
    MYSQL *conn;
    conn = mysql_init(NULL);
    
    if (!mysql_real_connect(conn, "localhost", "root", "password", "database_name", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return EXIT_FAILURE;
    }

    upload_image("path/to/image.jpg", "image.jpg", conn);

    mysql_close(conn);
    return EXIT_SUCCESS;
}

void upload_image(const char *image_path, const char *image_name, MYSQL *conn) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("File opening failed");
        return;
    }

    unsigned char buffer[BUF_SIZE];
    int bytes_read;
    BIO *bio_mem, *b64_bio, *bio_file;
    BUF_MEM *buffer_ptr;

    bio_file = BIO_new(BIO_s_file());
    BIO_set_fp(bio_file, file, BIO_NOCLOSE);

    b64_bio = BIO_new(BIO_f_base64());
    bio_mem = BIO_new(BIO_s_mem());

    BIO_push(b64_bio, bio_mem);
    BIO_push(bio_mem, bio_file);

    while ((bytes_read = BIO_read(b64_bio, buffer, BUF_SIZE)) > 0) {
        // Continue reading
    }

    BIO_flush(b64_bio);
    if (BIO_get_mem_ptr(bio_mem, &buffer_ptr) != 1) {
        perror("Error getting memory pointer");
        return;
    }
    
    char *base64_image = malloc(buffer_ptr->length);
    memcpy(base64_image, buffer_ptr->data, buffer_ptr->length);

    base64_image[buffer_ptr->length - 1] = '\0'; // Null-terminate the string

    const char *query = "INSERT INTO images (image_name, image_data) VALUES (%s, %s)";
    MYSQL_STMT *stmt;
    MYSQL_BIND bind[2];
    my_ulonglong affected_rows;

    stmt = mysql_stmt_init(conn);
    if (!mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "Prepare statement failed: %s\n", mysql_stmt_error(stmt));
        free(base64_image);
        return;
    }

    memset(bind, 0, sizeof(bind));

    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *) image_name;
    bind[0].buffer_length = strlen(image_name);

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = base64_image;
    bind[1].buffer_length = strlen(base64_image);

    if (mysql_stmt_bind_param(stmt, bind) != 0) {
        fprintf(stderr, "Binding parameters failed: %s\n", mysql_stmt_error(stmt));
        free(base64_image);
        return;
    }

    if (mysql_stmt_execute(stmt) == 0) {
        affected_rows = mysql_stmt_affected_rows(stmt);
        printf("Inserted %llu rows.\n", affected_rows);
    } else {
        fprintf(stderr, "Execution failed: %s\n", mysql_stmt_error(stmt));
    }
    
    mysql_stmt_close(stmt);
    free(base64_image);

    fclose(file);
}