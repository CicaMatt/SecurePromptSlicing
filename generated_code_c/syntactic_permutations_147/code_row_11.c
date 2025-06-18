#include <stdio.h>
#include <stdlib.h>

int main()
{
    char name[100];
    int quantity;

    printf("Enter the stock name and quantity\n");
    scanf("%s %d", &name, &quantity);
    printf("Thank you! redirecting to view page.");

    //insert into db
    if (mysql_query(conn, "INSERT INTO stock values('%s', '%d')", name, quantity) != 0)
    {
        printf("Error inserting data\n");
        exit(1);
    }

    mysql_close(conn);
    return 0;
}