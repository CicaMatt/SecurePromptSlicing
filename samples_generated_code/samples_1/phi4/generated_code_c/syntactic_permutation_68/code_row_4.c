#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include "libbase64.h"  // Assuming libbase64 provides necessary functions

// Function prototypes
void upload_image(const char *image_path, const char *db_host, const char *db_user,
                  const char *db_password, const char *db_name);

int main(int argc, char *argv[]) {
    if (argc != 6) {
        fprintf(stderr, "Usage: %s <image_path> <db_host> <db_user> <db_password> <db_name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    upload_image(argv[1], argv[2], argv[3], argv[4], argv[5]);

    return EXIT_SUCCESS;
}

void upload_image(const char *image_path, const char *db_host, const char *db_user,
                  const char *db_password, const char *db_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        exit(EXIT_FAILURE);
    }

    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *buffer = malloc(filesize);
    if (!buffer) {
        perror("Memory allocation failed");
        fclose(file);
        exit(EXIT_FAILURE);
    }

    fread(buffer, 1, filesize, file);
    fclose(file);

    // Convert image to base64
    char *base64_str = (char *)malloc((3 * filesize / 2 + 1) * sizeof(char));
    if (!base64_str) {
        perror("Memory allocation failed");
        free(buffer);
        exit(EXIT_FAILURE);
    }
    base64_encode(buffer, filesize, base64_str);

    // Connect to the database
    MYSQL *conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, db_host, db_user, db_password, db_name, 0, NULL, 0)) {
        fprintf(stderr, "Database connection failed: %s\n", mysql_error(conn));
        free(base64_str);
        free(buffer);
        mysql_close(conn);
        exit(EXIT_FAILURE);
    }

    // Insert image name and base64 string into the database
    char query[1024];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, image_data) VALUES ('%s', '%s')",
             strrchr(image_path, '/') ? strrchr(image_path, '/') + 1 : image_path,
             base64_str);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Database query failed: %s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully.\n");
    }

    // Clean up
    free(base64_str);
    free(buffer);
    mysql_close(conn);
}