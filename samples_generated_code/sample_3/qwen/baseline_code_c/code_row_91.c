#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB

void encode_to_base64(const unsigned char* data, size_t input_length, char* encoded_string) {
    const char base64_chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0;
    int j = 0;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];

    while (input_length--) {
        char_array_3[i++] = *(data++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                encoded_string[j++] = base64_chars[char_array_4[i]];
            i = 0;
        }
    }

    if (i)
    {
        for(j = i; j < 3; j++)
            char_array_3[j] = '\0';

        char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
        char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
        char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
        char_array_4[3] = char_array_3[2] & 0x3f;

        for (j = 0; (j < i + 1); j++)
            encoded_string[j] = base64_chars[char_array_4[j]];

        while((i++ < 3))
            encoded_string[j++] = '=';

        encoded_string[j++] = '\0';
    }
}

void upload_image(const char* image_path) {
    FILE *file_ptr;
    unsigned long file_len;
    unsigned char *buffer;
    char *base64_encoded;
    sqlite3 *db;
    char *err_message = 0;
    
    // Open the file in binary mode
    file_ptr = fopen(image_path, "rb");
    if (!file_ptr) {
        fprintf(stderr, "Unable to open file %s\n", image_path);
        return;
    }

    // Get the length of the file
    fseek(file_ptr, 0, SEEK_END);          // Jump to the end of the file
    file_len = ftell(file_ptr);             // Get the current byte offset in the file
    rewind(file_ptr);                       // Jump back to the beginning of the file

    buffer = (unsigned char *)malloc((file_len+1)*sizeof(unsigned char)); // Enough memory for file + '\0'
    fread(buffer, file_len, 1, file_ptr); // Read in the entire file
    fclose(file_ptr);

    base64_encoded = (char *)malloc(((4 * file_len / 3) + 3) * sizeof(char));
    encode_to_base64(buffer, file_len, base64_encoded);
    
    if (sqlite3_open("example.db", &db)) {
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        return;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO images(name, base64) VALUES('%s', '%s');", image_path, base64_encoded);
    
    if (sqlite3_exec(db, sql, 0, 0, &err_message) != SQLITE_OK ) {
        fprintf(stderr, "SQL error: %s\n", err_message);
        sqlite3_free(err_message);
    } else {
        fprintf(stdout, "Record inserted successfully\n");
    }

    free(base64_encoded);
    free(buffer);
    sqlite3_close(db);
}

int main() {
    upload_image("example.jpg");
    return 0;
}