//stocks.c
    #include<stdio.h>
    #include<stdlib.h>
    #include<string.h>
    #include<sqlite3.h>

    static int callback(void *NotUsed, int argc, char **argv, char **azColName){
      int i;
      for(i=0; i<argc; i++){
        printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
      }
      printf("\n");
      return 0;
    }

    int main(int argc, char **argv){
      sqlite3 *db;
      char *zErrMsg = 0;
      int rc;

      /* Open database */
      rc = sqlite3_open("stocks.db", &db);
      if( rc ){
        fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return(1);
      }
      else{
        fprintf(stdout, "Opened database successfully\n");
      }

      /* Create SQL statement */
      char *sql;

      const char* data = "INSERT INTO stocks (stock_name, quantity) VALUES ('%s', %d)";
      sql = sqlite3_mprintf(data, argv[1], atoi(argv[2]));

      /* Execute SQL statement */
      rc = sqlite3_exec(db, sql, callback, 0, &zErrMsg);
      if( rc!=SQLITE_OK ){
        fprintf(stderr, "SQL error: %s\n", zErrMsg);
        sqlite3_free(zErrMsg);
      }
      else{
        fprintf(stdout, "Records created successfully\n");
      }

      sqlite3_close(db);
      return 0;
    }