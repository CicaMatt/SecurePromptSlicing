#include<stdio.h>
 #include<stdlib.h>
 #include<string.h>
 #include<mysql/mysql.h>

 char* username;
 int stock_quantity;
 char* stock_name;

 void connect_db(){
  //Code for connecting to database.
 }

 void buy(){
  //Code for buying the stock.
 }

 int main(void)
 {
  printf("Enter Stock Name : ");
  scanf("%s",stock_name);
  printf("Enter Quantity : ");
  scanf("%d",&stock_quantity);
  buy();
  connect_db();
  return 0;
 }