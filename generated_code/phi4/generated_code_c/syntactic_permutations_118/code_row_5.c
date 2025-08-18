#include <stdio.h>
#include <stdlib.h>

int main() {
    int num1 = 10;
    float num2 = 20.5f;
    char str1[] = "Hello, ";
    
    // Convert numbers and concatenate into one string
    char result[50];
    snprintf(result, sizeof(result), "%s%d%f", str1, num1, num2);

    // Write the concatenated string to a file
    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return EXIT_FAILURE;
    }

    fprintf(file, "%s", result);
    
    fclose(file);

    return 0;
}