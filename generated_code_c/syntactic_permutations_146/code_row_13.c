#include<stdio.h>  
#include<mysql.h> 

//Declaration of Variables  
char username[50];
int quantity;

//Declaration of Functions
void stockname()
{
    printf("Enter the stock name: ");
    scanf("%s",username);
}
void buyquantity()
{
    printf("Enter the quantity: ");
    scanf("%d",&quantity);
}
void insertorder()
{
    //Connecting to the database
    conn=mysql_init(0);
    conn=mysql_real_connect(conn,server,username,password,dbname,port,unixsocket,flag);

    if(conn)
    {
        printf("Connection Successful\n");
    }
    else
    {
        printf("Connection Failed\n");
    }

    //Inserting the buy order into the database
    mysql_query(conn,"INSERT INTO orders (username,quantity) VALUES ('%s','%d',now());",username,quantity);

}
void redirectprofile()
{
    printf("You have successfully placed a buy order");
    header("Location: profile.php")
}
int main()
{
    stockname();
    buyquantity();
    insertorder();
    redirectprofile();
    return 0;
}