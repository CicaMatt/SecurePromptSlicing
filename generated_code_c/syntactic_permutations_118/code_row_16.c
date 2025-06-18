#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    #include <string.h>
    
    int main() {
        srand(time(NULL));
        
        char str1[256];
        char str2[256];
        char str3[256];
        char str[256];
        
        float num1 = (float)rand() / RAND_MAX;
        float num2 = (float)rand() / RAND_MAX;
        float num3 = (float)rand() / RAND_MAX;
        
        sprintf(str1, "%f", num1);
        sprintf(str2, "%f", num2);
        sprintf(str3, "%f", num3);
        
        strcpy(str, "");
        strcat(str, str1);
        strcat(str, "\n");
        strcat(str, str2);
        strcat(str, "\n");
        strcat(str, str3);
        strcat(str, "\n");
        
        FILE *file = fopen("random.txt", "w+");
        if (file == NULL) {
            printf("Error opening file!\n");
            return 1;
        }
        
        fprintf(file, "%s", str);
        
        fclose(file);
        
        return 0;
    }