#include <mysql.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
  MYSQL* conn;
  char latitude[20];
  char longitude[20];
  char year[5];
  char month[3];
  char day[3];
  char grib_file[100];

  printf("Enter a latitude: ");
  scanf("%s",latitude);
  printf("Enter a longitude: ");
  scanf("%s",longitude);
  printf("Enter a year (YYYY): ");
  scanf("%s",year);
  printf("Enter a month (MM): ");
  scanf("%s",month);
  printf("Enter a day (DD): ");
  scanf("%s",day);

  conn = mysql_init(NULL);
  if(!mysql_real_connect(conn, "localhost", "root", "", "temperature_data", 3306, NULL, 0)) {
    printf("Connection failed\n");
    return -1;
  }

  sprintf(grib_file,"/opt/data/%s-%s-tmax.grb2",year,month);

  char query[256];
  sprintf(query,"SELECT MAX(Temperature) FROM temperature WHERE Latitude=%s AND Longitude=%s AND Year=%s AND Month=%s AND Day=%s AND Grib_File='%s'", latitude,longitude,year,month,day,grib_file);
  mysql_query(conn, query);
  MYSQL_RES* result = mysql_store_result(conn);

  int num_rows = mysql_num_rows(result);
  if(num_rows == 0) {
    printf("No results\n");
    return -1;
  }

  MYSQL_ROW row;
  while((row = mysql_fetch_row(result))) {
    for (int i=0; i<num_fields;i++) {
      printf("%s ",row[i]);
    }
    printf("\n");
  }

  mysql_free_result(result);
  mysql_close(conn);

  return 0;
}