#include <stdio.h>
#include<string.h> 
int main()
{
    int usertype;
    printf("Enter 1 for user and 2 for admin: ");
    scanf("%d",&usertype);
    if(usertype==1)
    {
        printf("User page");
    }
    else if(usertype==2)
    {
        printf("Admin page");
    } 
}