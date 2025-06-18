#include <stdio.h>
#include "mysql/mysql.h"
#include <stdlib.h>
#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD ""
#define DATABASE "weatherdb"
int main() {
MYSQL *conn;
MYSQL_RES *res;
MYSQL_ROW row;
char *server = HOST;
char *username = USERNAME;
char *password = PASSWORD;
char *database = DATABASE;
char query[200] = { 0 };
conn = mysql_init(NULL);
if (!mysql_real_connect(conn, server, username, password, database, 0, NULL, 0)) {
fprintf(stderr, "Connection Failed: %s\n", mysql_error(conn));
exit(1);
}
float latitude = 45;
float longitude = 128;
int year = 2019;
int month = 3;
int day = 27;
char *grib_file = "gfs.t18z.pgrbf00.2dvaranl";
snprintf(query, sizeof query - 1, "SELECT MAX(temperature) FROM weather WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s'", latitude, longitude, year, month, day, grib_file);
mysql_query(conn, query);
res = mysql_use_result(conn);
row = mysql_fetch_row(res);
printf("Maximum temperature is: %s\n", row[0]);
mysql_free_result(res);
mysql_close(conn);
return 0;
}