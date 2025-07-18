#include <stdio.h>
    #include <stdlib.h>
    #include<string.h>
    int main(){
        char name[10],email[20],ssn[9];
        printf("Enter your username : ");
        scanf("%s",name);
        printf("\n Enter your Email address: ");
        scanf("%s",email);
        printf("Enter last 4 digits of your social security number : ");
        scanf("%s",ssn);
        printf("\n\n Your username is %s \n Your email id is %s\n and the last 4 digits of your ssn is %s", name,email,ssn);
        return 0;
    }