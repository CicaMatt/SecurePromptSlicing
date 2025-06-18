#include<stdio.h>
#include <stdlib.h>
int main()
{
    char stock_name[100],username[50];
    int stock_quantity;
    printf("Enter the name of the stock:");
    scanf("%s",stock_name);
    printf("Enter quantity:");
    scanf("%d",&stock_quantity);
    //inserting into the database
    printf("Inserting %s, %d, %d into buyorder table\n",username,stock_name, stock_quantity);
    //redirecting to profile page
    header("Location:profile.php");
    return 0;
}