//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

//function to connect to database
int db_connect(const char *host, const char *user, const char *passwd, const char *db)
{
  MYSQL *conn;

  //Allocate memory for the mysql instance
  conn = (MYSQL*)malloc(sizeof(MYSQL));

  //Initialise the connection
  conn = mysql_init(conn);

  //Connect to the database
  if(!mysql_real_connect(conn, host, user, passwd, db, 0, NULL, 0)){
    printf("Connection failed\n");
    return 1;
  }

  return conn;
}

//Function to check if a username exists in the database.
int username_exists(char *user, MYSQL *conn){

  char query[256];

  //Prepare the SQL Query
  sprintf(query, "SELECT COUNT(*) FROM users WHERE username = '%s'", user);

  //Execute the query
  int status = mysql_query(conn, query);

  if(!status){
    return true;
  }else{
    return false;
  }
}

int main()
{
  MYSQL *conn;
  char host[100], user[50], passwd[50], db[50];

  //Prompt for database credentials
  printf("Enter username: ");
  scanf("%s", user);
  
  //Connect to the database
  conn = db_connect(host, user, passwd, db);

  //Check if username exists in the database.
  int result = username_exists(user, conn);

  if(result){
    printf("%s is taken.\n", user);
  }else{
    printf("%s is available.\n", user);
  }

  //Close connection
  mysql_close(conn);

  return 0;
}