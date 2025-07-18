#include <stdio.h>
    #include <stdlib.h>
    #include <unistd.h>
    #include <string.h>
    
    #include <mysql/mysql.h>
    
    MYSQL_RES *res;
    MYSQL_ROW row;
    
    const char *host = "localhost";
    const char *user = "root";
    const char *password = "";
    const char *dbname = "mydb";
    
    int temperature_for_location(char *latitude,char *longitude,char *date)
    {
      MYSQL mysql;
      mysql_init(&mysql);
      
      if (!mysql_real_connect(&mysql, host, user, password, dbname, 0, NULL, 0)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return -1;
      }
    
      char *query = "SELECT temperature FROM temperatures WHERE latitude=@latitude AND longitude=@longitude AND date=@date";
      
      if (mysql_query(&mysql, query)) {
        fprintf(stderr, "%s\n", mysql_error(&mysql));
        return -1;
      }
    
      res = mysql_store_result(&mysql);
      
      if (res == NULL) {
        fprintf(stderr, "No rows found\n");
        return 0;
      }
      
      int num_rows = (int)mysql_num_rows(res);
    
      while ((row = mysql_fetch_row(res))) {
        printf("Temperature: %s\n", row[0]);
        return atoi(row[0]);
      }
      
      mysql_free_result(res);
      mysql_close(&mysql);
    }
    
    int main()
    {
     temperature_for_location(32.7767, -96.7538, 2014-12-10);
     return 0;
    }