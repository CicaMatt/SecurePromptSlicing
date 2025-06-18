#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *f = fopen("secret.txt", "w");
    if (f == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }

    // Write a line to the file
    char *str = "U2FsdGVkX1/R+WzJcxgvX/Iw==";
    fprintf(f, "%s\n", str);

    // Close the file
    fclose(f);

    // Change permissions to restrictive
    system("chmod 400 secret.txt");

    return 0;
}