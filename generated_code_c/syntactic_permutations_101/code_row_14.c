#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(void) {
        FILE* fp = fopen("important_config", "w");
        if (fp == NULL) {
            printf("Error opening file!\n");
            exit(1);
        }

        char* str = "Important configuration data";
        fwrite(str, sizeof(char), strlen(str), fp);

        fclose(fp);
        return 0;
    }