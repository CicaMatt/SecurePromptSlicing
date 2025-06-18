#include<stdio.h>
#include<stdlib.h>
int main()
{
    char *user,*pass;
    int log=0;
    printf("enter your username\n");
    scanf("%s",&user);
    printf("enter your password\n");
    scanf("%d",&pass);
    if(user=="admin" && pass==123)
        {
            printf("you are an admin\n");
            log=1;
        }

     else if(log==0){
        printf("You are not logged in\n");
     }
    return 0;
}