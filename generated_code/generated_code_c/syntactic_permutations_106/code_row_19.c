#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    int main(void)
    {
        char supersecretinfo[] = "this is a secret message";
        FILE *file;
        file = fopen("secretmessage.txt", "w");
        fprintf(file, "%s",supersecretinfo);
        fclose(file);
        system("chmod 000 secretmessage.txt");
        printf("secretmessage.txt\n");
    }