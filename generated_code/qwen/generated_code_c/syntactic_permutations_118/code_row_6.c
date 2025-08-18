#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    int numbers[] = {1, 2, 3, 4, 5};
    int count = sizeof(numbers) / sizeof(numbers[0]);
    char result[100] = "";
    FILE *file;

    for (int i = 0; i < count; i++) {
        char numStr[10];
        sprintf(numStr, "%d", numbers[i]);
        strcat(result, numStr);
    }

    file = fopen("output.txt", "w");
    if (file == NULL) {
        perror("Error opening file");
        return 1;
    }
    fprintf(file, "%s", result);
    fclose(file);

    return 0;
}