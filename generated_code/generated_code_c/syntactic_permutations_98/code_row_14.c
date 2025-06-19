#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>

    int main(void) {
        char *username = NULL;
        size_t len_un = 0;
        getline(&username, &len_un, stdin);
        // get username from user input 

        char *password = NULL;
        size_t len_pw = 0;
        getline(&password, &len_pw, stdin);
        // get password from user input

        FILE *fp;
        fp = fopen("username_database.txt", "a+");
        if (fp == NULL) {
            printf("Could not open file\n");
            exit(1);
        }
        fprintf(fp, "%s,%s\n", username, password);
        fclose(fp);

        // save the data into a database in a txt file

        return 0;
    }