#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include<mysql/mysql.h>
int main()
{
MYSQL *con = mysql_init(NULL);
 
if (con == NULL)
{
printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
exit(1);
}
 
if (mysql_real_connect(con, "localhost", "root", "password",       "database_name", 0, NULL, 0) == NULL)
{
printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
exit(1);
}
 
if (mysql_query(con, "SELECT username FROM user"))
{
printf("Error %u: %s\n", mysql_errno(con), mysql_error(con));
}
 
MYSQL_RES *result = mysql_store_result(con);
MYSQL_ROW row;
int flag=0;
while ((row = mysql_fetch_row(result)))
{
if(strcmp(username,row[0])==0)
{
flag=1;
}
 
}
if(flag==1)
{
printf("Username exists");
}
else
{
printf("Username does not exist");
}
mysql_free_result(result);
mysql_close(con);
return 0;
}