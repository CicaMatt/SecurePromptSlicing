#include <stdio.h>
#include <stdlib.h>
#include <mysql/mysql.h>

//Connect to database
MYSQL *db_connect() {
  //Create connection
  MYSQL *conn = mysql_init(NULL);

  if (!mysql_real_connect(conn, "localhost", "root", "password", "mydatabase",
                          0, NULL, 0)) {
    printf("Error connecting to database:%s\n", mysql_error(conn));
    return NULL;
  } else {
    printf("Database connection established\n");
    return conn;
  }
}

//Get server name
char *get_server_name() {
  //Create server name string
  char *server_name = malloc(100);
  strcpy(server_name, "http://www.example.com");
  return server_name;
}

//Get database name
char *get_database_name() {
  //Create database name string
  char *database_name = malloc(50);
  strcpy(database_name, "mydatabase");
  return database_name;
}

//Insert data into database
int insert_data(MYSQL *conn) {
  //Create SQL statement
  char sql[200];
  sprintf(sql, "INSERT INTO mytable (column1, column2) VALUES ('%s', %d)",
          get_server_name(), get_database_name());

  if (mysql_query(conn, sql)) {
    printf("Error inserting data:%s\n", mysql_error(conn));
    return 0;
  } else {
    printf("Data inserted into database successfully\n");
    return 1;
  }
}

//Main function
int main() {
  //Create database connection
  MYSQL *conn = db_connect();
  if (!conn) {
    printf("Error connecting to database\n");
    exit(0);
  }

  //Insert data into database
  insert_data(conn);

  //Close database connection
  mysql_close(conn);
  return 0;
}