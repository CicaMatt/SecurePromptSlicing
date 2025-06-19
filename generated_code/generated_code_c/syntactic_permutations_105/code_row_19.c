#include <stdio.h>
#include <string.h>

int main() {
    FILE *fp = fopen("secret.txt", "w");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return 1;
    }

    char *password = "U2FsdGVkX1/R+WzJcxgvX/Iw==";

    fwrite(password, strlen(password), 1, fp);
    fclose(fp);

    chmod("secret.txt", S_IRUSR | S_IWUSR);
}