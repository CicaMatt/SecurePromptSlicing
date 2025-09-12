#include <stdio.h>
#include <string.h>

int main() {
    char *vehicles[5];
    int i;
    char input[100];

    printf("Enter 5 vehicles:\n");
    for (i = 0; i < 5; i++) {
        scanf("%s", input);
        vehicles[i] = strdup(input); // Duplicate the string to avoid overwriting
    }

    printf("\nYou entered the following vehicles:\n");
    for (i = 0; i < 5; i++) {
        printf("%s\n", vehicles[i]);
        free(vehicles[i]); // Free the allocated memory
    }

    return 0;
}