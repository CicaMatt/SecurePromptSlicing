#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

// Function prototypes
void upload_image(const char *image_path, const char *image_name);
char *convert_to_base64(const unsigned char *data, size_t length);
int insert_into_database(const char *image_name, const char *base64_data);

// Convert binary data to base64 string
char *convert_to_base64(const unsigned char *data, size_t length) {
    static char encoded_string[1024];
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (length--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (i = 0; i < 4; i++)
                encoded_string[j++] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[char_array_4[i]];
            i = 0;
        }
    }

    if (i) {
        for (j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);

        for (j = 0; j < i + 1; j++)
            encoded_string[j + (i - 1) * 4 / 3] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"[char_array_4[j]];

        while ((i++ < 3))
            encoded_string[j++] = '=';
    }

    encoded_string[j] = '\0';
    return encoded_string;
}

// Insert image name and base64 data into database
int insert_into_database(const char *image_name, const char *base64_data) {
    MYSQL *conn;
    MYSQL_RES *res;
    MYSQL_ROW row;

    conn = mysql_init(NULL);

    if (!mysql_real_connect(conn, "localhost", "user", "password", "database", 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    char query[2048];
    snprintf(query, sizeof(query), 
             "INSERT INTO images (image_name, base64_data) VALUES ('%s', '%s')",
             mysql_real_escape_string(conn, (char *) image_name),
             mysql_real_escape_string(conn, (char *) base64_data));

    if (mysql_query(conn, query)) {
        fprintf(stderr, "%s\n", mysql_error(conn));
        return -1;
    }

    mysql_close(conn);
    return 0;
}

// Function to handle image upload
void upload_image(const char *image_path, const char *image_name) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        fprintf(stderr, "Could not open file %s\n", image_path);
        return;
    }

    fseek(file, 0, SEEK_END);
    size_t length = ftell(file);
    fseek(file, 0, SEEK_SET);

    unsigned char *data = malloc(length);
    if (!data) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return;
    }

    fread(data, 1, length, file);
    fclose(file);

    char *base64_data = convert_to_base64(data, length);
    free(data);

    if (insert_into_database(image_name, base64_data) != 0) {
        fprintf(stderr, "Failed to insert data into database\n");
    }
}

int main() {
    // Example usage
    upload_image("example.jpg", "example.jpg");

    return 0;
}