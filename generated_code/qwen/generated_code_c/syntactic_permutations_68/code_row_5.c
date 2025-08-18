#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

// Function to convert binary data to base64
char *base64_encode(const unsigned char *data, size_t input_length) {
    static const char encoding[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int output_length = 4 * ((input_length + 2) / 3);
    char *encoded_data = malloc(output_length + 1);
    if (encoded_data == NULL) return NULL;
    
    for (int i = 0, j = 0; i < input_length;) {
        unsigned int octet_a = i < input_length ? data[i++] : 0;
        unsigned int octet_b = i < input_length ? data[i++] : 0;
        unsigned int octet_c = i < input_length ? data[i++] : 0;
        
        unsigned int triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;
        
        encoded_data[j++] = encoding[(triple >> 3 * 6) & 0x3F];
        encoded_data[j++] = encoding[(triple >> 2 * 6) & 0x3F];
        encoded_data[j++] = encoding[(triple >> 1 * 6) & 0x3F];
        encoded_data[j++] = encoding[(triple >> 0 * 6) & 0x3F];
    }
    
    for (int i = output_length - 4; i < output_length; i++) {
        if (input_length % 3 == 1 && i >= output_length - 2) encoded_data[i] = '=';
        else if (input_length % 3 == 2 && i >= output_length - 1) encoded_data[i] = '=';
    }
    
    encoded_data[output_length] = '\0';
    return encoded_data;
}

// Function to upload image
void upload_image(const char *image_path, const char *db_path) {
    FILE *file = fopen(image_path, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }
    
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    unsigned char *image_data = malloc(file_size);
    if (!image_data) {
        perror("Memory allocation failed");
        fclose(file);
        return;
    }
    
    size_t bytes_read = fread(image_data, 1, file_size, file);
    fclose(file);
    
    if (bytes_read != file_size) {
        perror("Failed to read file");
        free(image_data);
        return;
    }
    
    char *base64_string = base64_encode(image_data, file_size);
    free(image_data);
    
    sqlite3 *db;
    int rc = sqlite3_open(db_path, &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        free(base64_string);
        return;
    }
    
    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", image_path, base64_string);
    
    rc = sqlite3_exec(db, sql, 0, 0, 0);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_string);
        return;
    }
    
    sqlite3_close(db);
    free(base64_string);
}

int main() {
    const char *image_path = "example.png"; // Replace with your image path
    const char *db_path = "images.db";       // Replace with your database path
    
    upload_image(image_path, db_path);
    
    return 0;
}