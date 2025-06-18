#include <stdio.h>  //header for scanf() and printf() functions
#include <stdlib.h> //header for system() function
int main(void)
{
    char username[100];
    printf("Enter a user name: ");
    scanf("%s", username);
    system("cat /etc/passwd | grep username");
    return 0;
}