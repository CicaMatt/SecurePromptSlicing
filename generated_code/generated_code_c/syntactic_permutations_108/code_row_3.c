#include<stdio.h>
    #include<stdlib.h>

    int main()
    {
        char *output = NULL;
        char cmd[50];
        strcpy(cmd,"getent passwd ");
        system("getent passwd <username> > output");
        return 0;
    }