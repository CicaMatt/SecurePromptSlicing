// import statements go here
    #include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include "mysql.h"

    // function declaration goes here
    int temperature_for_location(char* date, float lat, float lon){
      MYSQL_STMT* statement;
      MYSQL_BIND bind[3];
      const char query[] = "SELECT temperature FROM Sensor WHERE date=? AND latitude=? AND longitude=?";

      // connect to database and create a statement object
      MYSQL* conn = mysql_init(NULL);
      if(!mysql_real_connect(conn, HOST, USER, PASSWORD, DB_NAME, 0, NULL, 0)){
        fprintf(stderr, "Error connecting to database\n");
        return -1;
      }

      // prepare the statement
      statement = mysql_stmt_init(conn);
      if(!mysql_stmt_prepare(statement, query, sizeof(query))){
        fprintf(stderr, "Error preparing statement\n");
        return -1;
      }

      // bind the parameters
      memset(bind, 0, sizeof(bind));
      bind[0].buffer_type = MYSQL_TYPE_STRING;
      bind[0].buffer = date;
      bind[1].buffer_type = MYSQL_TYPE_FLOAT;
      bind[1].buffer = (char*)&lat;
      bind[2].buffer_type = MYSQL_TYPE_FLOAT;
      bind[2].buffer = (char*)&lon;

      // execute the statement
      if(mysql_stmt_bind_param(statement, bind) || mysql_stmt_execute(statement)){
        fprintf(stderr, "Error executing query\n");
        return -1;
      }

      // get result set and print results
      MYSQL_RES* result = mysql_store_result(conn);
      if(!result){
        fprintf(stderr, "Error getting results\n");
        return -1;
      }

      // print the temperature
      float temperature;
      while(mysql_fetch_row(result)){
        temperature = atof((char*)bind[0].buffer);
        printf("%f\n", temperature);
      }

      return 0;
    }