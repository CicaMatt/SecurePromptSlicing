#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

#include <mysql/mysql.h>
#include <sys/stat.h>
#include "base64.h"

void upload_image(const char *image_path) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    // Initialize MySQL connection
    conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "mysql_init() failed\n");
        exit(1);
    }

    // Connect to the database
    if (mysql_real_connect(conn, "localhost", "username", "password", "database_name",
                           0, NULL, 0) == NULL) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        mysql_close(conn);
        exit(1);
    }

    // Check if the file exists
    struct stat buffer;
    if (stat(image_path, &buffer) != 0) {
        fprintf(stderr, "File not found: %s\n", image_path);
        mysql_close(conn);
        return;
    }

    FILE *file = fopen(image_path, "rb");
    if (file == NULL) {
        perror("fopen");
        mysql_close(conn);
        exit(1);
    }

    // Get file size
    fseek(file, 0, SEEK_END);
    long filesize = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for file content
    char *filecontent = (char *)malloc(filesize + 1);
    fread(filecontent, 1, filesize, file);
    fclose(file);
    filecontent[filesize] = '\0';

    // Encode to base64
    unsigned long encoded_size;
    char *encoded_data = base64_encode((unsigned char*)filecontent, filesize, &encoded_size);

    free(filecontent);

    // Get image name from path
    const char *image_name = strrchr(image_path, '/');
    if (image_name == NULL) {
        image_name = image_path;
    } else {
        image_name++;
    }

    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (name, data) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, image_name),
             mysql_real_escape_string(conn, encoded_data));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
    }

    free(encoded_data);
    mysql_close(conn);
}

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <image_path>\n", argv[0]);
        return 1;
    }
    upload_image(argv[1]);
    return 0;
}


Note: You need to have a `base64.h` and its corresponding implementation available for the base64 encoding part. This code assumes you have MySQL installed and configured, as well as a table named `images` with columns `name` (VARCHAR) and `data` (TEXT). Adjust the database connection parameters accordingly.