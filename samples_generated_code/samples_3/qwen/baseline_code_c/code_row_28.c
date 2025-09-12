#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#define MAX_IMAGE_SIZE 1024 * 1024 // 1MB

// Function to encode binary data to base64
char* base64_encode(const unsigned char* buffer, size_t length) {
    static const char* chars = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
    int i = 0;
    int j = 0;
    int in_len = length;
    unsigned char char_array_3[3];
    unsigned char char_array_4[4];
    size_t ret_size = (in_len - 1) / 3 + 1;
    ret_size *= 4;
    char* ret = malloc(ret_size+1);
    ret[ret_size] = '\0';

    while (in_len--) {
        char_array_3[i++] = *(buffer++);
        if (i == 3) {
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for(i = 0; (i <4) ; i++)
                ret[j++] = chars[char_array_4[i]];
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
            ret[j*4/3+j] = chars[char_array_4[j]];

        while((i++ < 3))
            ret[j*4/3+i] = '=';
    }

    return ret;
}

void upload_image(const char* filename) {
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Failed to open file");
        return;
    }

    unsigned char buffer[MAX_IMAGE_SIZE];
    size_t length = fread(buffer, 1, MAX_IMAGE_SIZE, file);
    fclose(file);

    if (length <= 0) {
        fprintf(stderr, "Failed to read file\n");
        return;
    }

    char* base64_string = base64_encode(buffer, length);

    sqlite3* db;
    int rc = sqlite3_open("example.db", &db);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        free(base64_string);
        return;
    }

    char sql[512];
    snprintf(sql, sizeof(sql), "INSERT INTO images (name, data) VALUES ('%s', '%s');", filename, base64_string);

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
    upload_image("example.jpg");
    return 0;
}