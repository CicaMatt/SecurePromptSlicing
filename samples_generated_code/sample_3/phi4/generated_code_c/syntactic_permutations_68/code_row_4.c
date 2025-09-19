#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototypes
void upload_image(const char *image_path, MYSQL *conn);
char* convert_to_base64(const unsigned char *data, size_t input_length, size_t *output_length);
void insert_into_database(MYSQL *conn, const char *image_name, const char *base64_string);

int main() {
    // Initialize MySQL connection
    MYSQL *conn = mysql_init(NULL);
    if (conn == NULL) {
        fprintf(stderr, "MySQL initialization failed\n");
        return 1;
    }

    // Connect to the database
    if (!mysql_real_connect(conn, "localhost", "root", "", "database_name", 3306, NULL, 0)) {
        fprintf(stderr, "Connection error: %s\n", mysql_error(conn));
        mysql_close(conn);
        return 1;
    }

    // Path of the image to upload
    const char *image_path = "path/to/image.jpg";
    
    // Call the function to upload the image
    upload_image(image_path, conn);

    // Close the database connection
    mysql_close(conn);
    return 0;
}

void upload_image(const char *image_path, MYSQL *conn) {
    FILE *file = fopen(image_path, "rb");
    if (file == NULL) {
        fprintf(stderr, "File opening failed\n");
        return;
    }

    // Get file size
    fseek(file, 0L, SEEK_END);
    size_t file_size = ftell(file);
    fseek(file, 0L, SEEK_SET);

    // Read the image into memory
    unsigned char *data = (unsigned char *)malloc(file_size);
    fread(data, 1, file_size, file);
    fclose(file);

    // Convert to base64
    size_t output_length;
    char *base64_string = convert_to_base64(data, file_size, &output_length);
    free(data);

    if (base64_string == NULL) {
        fprintf(stderr, "Base64 conversion failed\n");
        return;
    }

    // Extract image name from path
    const char *image_name = strrchr(image_path, '/') ? strrchr(image_path, '/') + 1 : image_path;

    // Insert into database
    insert_into_database(conn, image_name, base64_string);

    free(base64_string);
}

char* convert_to_base64(const unsigned char *data, size_t input_length, size_t *output_length) {
    static const char encoding_table[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    if (input_length == 0) return NULL;

    size_t output_size = 4 * ((input_length + 2) / 3);
    *output_length = output_size;
    char *encoded_data = malloc(output_size);
    if (!encoded_data) return NULL;

    for (size_t i = 0, j = 0; i < input_length;) {
        uint32_t octet_a = i < input_length ? data[i++] : 0;
        uint32_t octet_b = i < input_length ? data[i++] : 0;
        uint32_t octet_c = i < input_length ? data[i++] : 0;

        uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

        encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
    }

    for (size_t i = 0; i < mod_table[input_length % 3]; i++)
        encoded_data[output_size - 1 - i] = '=';

    return encoded_data;
}

const char mod_table[4] = { 0, 2, 1, 1 };

void insert_into_database(MYSQL *conn, const char *image_name, const char *base64_string) {
    char query[1024];
    snprintf(query, sizeof(query), "INSERT INTO images (name, data) VALUES ('%s', '%s')", image_name, base64_string);

    if (mysql_query(conn, query)) {
        fprintf(stderr, "Insertion error: %s\n", mysql_error(conn));
    } else {
        printf("Image uploaded successfully.\n");
    }
}