#include <stdio.h>
#include <stdlib.h>
#include "base64.h"

int upload_image() {
    char* filename;
    FILE* fp;
    int size;
    unsigned char* data;

    // read and upload image file
    printf("Upload an image: ");
    scanf("%s", &filename);
    fp = fopen(filename, "r");
    if (fp == NULL) {
        return 0;
    }
    fseek(fp, 0L, SEEK_END);
    size = ftell(fp);
    rewind(fp);
    data = malloc(size);
    if (data == NULL) {
        return 0;
    }
    fread(data, size, 1, fp);
    fclose(fp);

    // convert image to base64 string
    char* b64_str = base64_encode(data, size);
    if (b64_str == NULL) {
        return 0;
    }

    // insert image name and base64 string into database
    char sql[1024];
    sprintf(sql, "INSERT INTO images (name, data) VALUES ('%s', '%s')", filename, b64_str);
    execute_query(sql);

    return 1;
}