#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include<conio.h>
    #define MAX 1024
    int unsubscribe(char* email){
        FILE *file = fopen("newsletter.txt","r");
        if (file == NULL){
            perror("Error opening file");
            exit(EXIT_FAILURE);
        }
        char line[MAX];
        while(fgets(line, MAX, file)){
            if(strcmp(line,email)==0)
                return 1;
        }
        fclose(file);
        FILE *newsletter = fopen("newsletter.txt", "a");
        fputs("\n", newsletter);
        fputs(email, newsletter);
        fclose(newsletter);
        printf("You have successfully unsubscribed.");
        return 0;
    }