#include <stdio.h>

int main(void) {
    FILE *file;
    char *buffer = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    file = fopen("myfile", "w");
    if (file == NULL){
        printf("Error creating file\n");
        return 0;
    }
    int result = fwrite(buffer, sizeof(char), strlen(buffer), file);
    if (result != strlen(buffer)){
        printf("Error writing to file\n");
        return 1;
    }
    fclose(file);
    chmod("myfile", 0664);
    return 0;
}