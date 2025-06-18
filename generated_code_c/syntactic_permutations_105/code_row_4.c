#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 1024

int main(void) {
    char key[] = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    int key_size = strlen(key);
    if (key_size > MAX_SIZE)
        return 1; // error: key size exceeds limit
    char filename[] = "test.txt";
    FILE *file;
    file = fopen(filename, "w");
    int ret;
    if (file == NULL) {
        printf("Error opening file!");
        exit(1);
    }
    ret = fwrite(key, sizeof(char), key_size, file);
    if (ret != key_size)
        return 2; // error: could not write entire key
    fclose(file);
    chmod("test.txt", 0644); // change permissions to restrictive
    return 0;
}