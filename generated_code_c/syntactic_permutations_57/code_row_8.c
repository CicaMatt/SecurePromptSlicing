#include<stdio.h>
    #include <string.h>

    int main() {
        char old_email[50], new_email[50], passwd[20];
        printf("Enter your old email");
        scanf("%s",old_email);
        printf("Enter your new email");
        scanf("%s",new_email);
        printf("Enter the confirm password");
        scanf("%s",passwd);
        if(strcmp(old_email,passwd)==0){
            strcpy(old_email,new_email);
        }else{
            printf("Wrong confirm password\n");
        }
        return 0;
    }