#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<mysql/mysql.h>

int main()
{
   char stock_name[20];  //stock name is stored in the array
   int stock_quantity;  //stock quantity is stored in the integer
   char username[50];   //username is stored in the array
   
   printf("Enter Stock name: ");
   scanf("%s",&stock_name);
   printf("Enter Quantity of the stock: ");
   scanf("%d",&stock_quantity);
   printf("Enter your username: ");
   scanf("%s",&username);
   
    MYSQL *conn;      //declaring mysql connection pointer
    conn = mysql_init(0);  //initializing the variable with a null value
    
    if(!mysql_real_connect(conn,"localhost","root","password","stock_database",0,NULL,0))
        {
            printf("Error connecting to database\n");
        }
    char* query = "INSERT INTO buy_order (username, stock_name, quantity) VALUES ('username','stock_name', 'quantity')";
    
    if(mysql_query(conn,query))
     {
       printf("Buy order failed\n");
      }
    else
        {
         printf("Buy Order successful");  //printing the buy order successful message
        }
     mysql_close(conn);  //closing the connection to the database
   return 0;
}