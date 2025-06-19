#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <sys/types.h>
    #include <sys/stat.h>

    typedef struct {
        char* name;
        int size;
        void* data;
    } file_t;

    // Function to upload the file
    int upload_file(const char* filename) {
        FILE* pFile = fopen(filename, "rb");
        if (pFile == NULL) {
            printf("Error opening %s\n", filename);
            return -1;
        }
        // Read the file into a buffer.
        fseek(pFile, 0L, SEEK_END);
        long size = ftell(pFile);
        rewind(pFile);
        char* data = malloc(sizeof(char) * size);
        if (data == NULL) {
            printf("Error allocating %ld bytes\n", size);
            fclose(pFile);
            return -1;
        }
        // Read the file into a buffer.
        fread(data, sizeof(char), size, pFile);
        // Save the file to the uploads folder.
        char* dirname = "uploads";
        if (mkdir(dirname) == -1) {
            printf("Error creating directory %s\n", dirname);
            free(data);
            fclose(pFile);
            return -1;
        }
        file_t* p = malloc(sizeof(file_t));
        if (p == NULL) {
            printf("Error allocating file_t struct\n");
            free(data);
            fclose(pFile);
            return -1;
        }
        p->name = filename;
        p->size = size;
        p->data = data;
        // Save the file to the uploads folder.
        char* new_filename = malloc(strlen(dirname) + strlen(p->name) + 2);
        if (new_filename == NULL) {
            printf("Error allocating string for filename\n");
            free(data);
            fclose(pFile);
            return -1;
        }
        sprintf(new_filename, "%s/%s", dirname, p->name);
        FILE* qFile = fopen(new_filename, "wb");
        if (qFile == NULL) {
            printf("Error opening %s for writing\n", new_filename);
            free(data);
            fclose(pFile);
            return -1;
        }
        // Write the buffer to the file.
        fwrite(p->data, sizeof(char), p->size, qFile);
        printf("Successfully uploaded %s\n", filename);
        free(new_filename);
        free(data);
        fclose(qFile);
        return 0;
    }