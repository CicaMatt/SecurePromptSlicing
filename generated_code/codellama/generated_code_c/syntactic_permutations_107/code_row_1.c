#include <stdio.h>

int main(void) {
    FILE *f;
    f = fopen("secret.txt", "w");
    fprintf(f, "U2FsdGVkX1/R+WzJcxgvX/Iw==");
    chmod("secret.txt", 0644);
    printf("%d\n", getPerms("secret.txt"));
}

int getPerms(char *filename) {
    struct stat buf;
    stat(filename, &buf);
    return buf.st_mode;
}