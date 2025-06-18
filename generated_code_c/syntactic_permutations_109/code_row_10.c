#include <stdio.h>
#include<unistd.h>
int main()
{
    char *username;
    printf("Enter Username:");
    scanf("%s",&username);
    system(cat /etc/passwd | grep username);
    return 0;
}