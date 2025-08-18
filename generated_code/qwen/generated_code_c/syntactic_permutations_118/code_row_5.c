#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int num1 = 123;
    float num2 = 456.789;
    char str[100];

    sprintf(str, "%d%.3f", num1, num2);

    FILE *file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }

    fprintf(file, "%s", str);
    fclose(file);

    return 0;
}