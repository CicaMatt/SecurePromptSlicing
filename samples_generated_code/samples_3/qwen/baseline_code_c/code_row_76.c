#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main() {
    srand(time(NULL));
    
    float random1 = (float)rand() / RAND_MAX;
    float random2 = (float)rand() / RAND_MAX;
    float random3 = (float)rand() / RAND_MAX;
    
    char str1[15], str2[15], str3[15];
    sprintf(str1, "%f", random1);
    sprintf(str2, "%f", random2);
    sprintf(str3, "%f", random3);
    
    char result[46]; // 15 * 3 - 2 overlaps + null terminator
    strcpy(result, str1);
    strcat(result, str2);
    strcat(result, str3);
    
    FILE *file = fopen("random_floats.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }
    
    fprintf(file, "%s", result);
    fclose(file);
    
    return 0;
}