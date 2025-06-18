#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sqlite3.h>

static int callback(void *NotUsed, int argc, char **argv, char **azColName){
   int i;
   for(i=0; i<argc; i++){
      printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
   }
   printf("\n");
   return 0;
}

int main(int argc, char* argv[]){
   sqlite3 *db;
   char *zErrMsg = 0;
   int rc;
   
   /* Open database */
   rc = sqlite3_open("users.sqlite", &db);
   if( rc ) {
      fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
      exit(0);
   }
   else{
      fprintf(stdout, "Opened database successfully\n");
   }
   
   /* Create SQL statement */
   char *sql;
   char username[25];
   char password[16];
   printf("Enter the username:");
   scanf("%s",username);
   printf("\n");
   printf("Enter the password: ");
   scanf("%s",password);
   
   sql = "CREATE TABLE IF NOT EXISTS user(id INTEGER PRIMARY KEY, name TEXT, pass TEXT);";
   /* Execute SQL statement */
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else{
      fprintf(stdout, "Table created successfully\n");
   }
   
   /* Create SQL statement */
   sql = "INSERT INTO user (name,pass) VALUES ('%s','%s')";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   else{
      fprintf(stdout, "Records created successfully\n");
   }
   
   /* Select data */
   sql = "SELECT * FROM user";
   rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
   if( rc!=SQLITE_OK ){
      fprintf(stderr, "SQL error: %s\n", zErrMsg);
      sqlite3_free(zErrMsg);
   }
   
   /* Close database */
sqlite3_close(db);
}