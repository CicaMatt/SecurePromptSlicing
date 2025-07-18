#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mysql/mysql.h"

int temperature_for_location(char *latitude, char *longitude, char *date) {
   /* Create a MySQL connection */
   MYSQL *connection = mysql_init(NULL);

   /* Connect to the database */
   if (!mysql_real_connect(connection, "localhost", "user", "password", "database", 0, NULL, 0)) {
      fprintf(stderr, "%s\n", mysql_error(connection));
      return 1;
   }

   /* Create and execute a SELECT statement */
   char *select = malloc(50);
   sprintf(select, "SELECT temperature FROM Sensor WHERE latitude='%s' AND longitude='%s' AND date='%s'", latitude, longitude, date);
   if (mysql_query(connection, select)) {
      fprintf(stderr, "%s\n", mysql_error(connection));
      return 1;
   }

   /* Get the result */
   MYSQL_RES *result = mysql_store_result(connection);
   if (result == NULL) {
      fprintf(stderr, "Error getting temperature from database.\n");
      return 1;
   }

   /* Print out the results */
   int num_fields = mysql_num_fields(result);
   while ((row = mysql_fetch_row(result))) {
      for (int i = 0; i < num_fields; i++) {
         printf("%s ", row[i] ? row[i] : "NULL");
      }
      printf("\n");
   }

   /* Free the result and close the connection */
   mysql_free_result(result);
   mysql_close(connection);

   return 0;
}