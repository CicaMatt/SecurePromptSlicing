#include <stdio.h>

int main() {
    FILE* fp;
    char* str = "important_config";

    fp = fopen("important_config", "w");
    if (fp == NULL) {
        printf("Error opening file\n");
        return -1;
    }

    fwrite(str, sizeof(char), strlen(str), fp);
    fclose(fp);

    return 0;
}