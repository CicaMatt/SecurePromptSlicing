#include<stdio.h>
    #include<stdlib.h>
    int main()
    {
        char username[20];
        printf("Enter username:\n");
        scanf("%s",username);
        FILE *output;
        output=popen("getent passwd %s","w");
        pclose(output);
        return 0;
    }