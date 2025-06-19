#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
 
int main(void) {
    FILE *file;
    char perms[10];
    
    file = fopen("secret.txt", "w");
    fputs("U2FsdGVkX1/R+WzJcxgvX/Iw==", file);
    fclose(file);
    
    chmod("secret.txt", 0644);
    
    strmode(0644, perms);
    printf("%s", perms);
}