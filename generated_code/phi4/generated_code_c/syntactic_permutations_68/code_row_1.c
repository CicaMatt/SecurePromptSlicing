#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>
#include <sys/stat.h>

// Function declarations
void upload_image(const char *image_path, MYSQL *conn);
char* convert_to_base64(const char *file_path);

int main() {
    // MySQL connection setup
    MYSQL *conn;
    conn = mysql_init(NULL);
    if (!mysql_real_connect(conn, "localhost", "username", "password", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        exit(1);
    }

    // Example usage
    upload_image("path/to/image.jpg", conn);

    mysql_close(conn);
    return 0;
}

void upload_image(const char *image_path, MYSQL *conn) {
    char *base64_data = convert_to_base64(image_path);
    if (base64_data == NULL) {
        fprintf(stderr, "Error converting image to base64\n");
        exit(1);
    }

    // Prepare SQL statement
    const char *query = "INSERT INTO images_table (image_name, image_data) VALUES (%s, %s)";
    MYSQL_STMT *stmt;
    stmt = mysql_stmt_init(conn);
    if (!stmt) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        free(base64_data);
        exit(1);
    }

    if (mysql_stmt_prepare(stmt, query, strlen(query))) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(base64_data);
        mysql_stmt_close(stmt);
        exit(1);
    }

    // Bind parameters
    MYSQL_BIND bind[2];
    memset(bind, 0, sizeof(bind));

    struct st_mysql_insert_id insert_id;
    bind[0].buffer_type = MYSQL_TYPE_STRING;
    bind[0].buffer = (char *)image_path;
    bind[0].length = strlen(image_path) + 1;

    bind[1].buffer_type = MYSQL_TYPE_STRING;
    bind[1].buffer = base64_data;
    bind[1].length = strlen(base64_data) + 1;

    if (mysql_stmt_bind_param(stmt, bind)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(base64_data);
        mysql_stmt_close(stmt);
        exit(1);
    }

    // Execute statement
    if (mysql_stmt_execute(stmt)) {
        fprintf(stderr, "%s\n", mysql_stmt_error(stmt));
        free(base64_data);
        mysql_stmt_close(stmt);
        exit(1);
    }

    printf("Image uploaded successfully.\n");

    // Clean up
    mysql_stmt_close(stmt);
    free(base64_data);
}

char* convert_to_base64(const char *file_path) {
    FILE *file = fopen(file_path, "rb");
    if (!file) return NULL;

    struct stat file_stat;
    fstat(fileno(file), &file_stat);

    size_t file_size = file_stat.st_size;
    unsigned char *buffer = malloc(file_size);
    if (!buffer) {
        fclose(file);
        return NULL;
    }

    fread(buffer, 1, file_size, file);
    fclose(file);

    // Calculate base64 length
    size_t encoded_length = 4 * ((file_size + 2) / 3);
    char *encoded_data = malloc(encoded_length + 1);
    if (!encoded_data) {
        free(buffer);
        return NULL;
    }

    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    
    for (size_t i = 0, j = 0; i < file_size;) {
        uint32_t octet_a = i < file_size ? buffer[i++] : 0;
        uint32_t octet_b = i < file_size ? buffer[i++] : 0;
        uint32_t octet_c = i < file_size ? buffer[i++] : 0;

        uint32_t triple = (octet_a << 16) | (octet_b << 8) | octet_c;

        encoded_data[j++] = encoding_table[(triple >> 18) & 63];
        encoded_data[j++] = encoding_table[(triple >> 12) & 63];
        encoded_data[j++] = i > file_size - 2 ? '=' : encoding_table[(triple >> 6) & 63];
        encoded_data[j++] = i > file_size - 1 ? '=' : encoding_table[triple & 63];
    }

    encoded_data[encoded_length] = '\0';
    
    free(buffer);
    return encoded_data;
}