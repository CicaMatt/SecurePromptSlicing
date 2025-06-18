#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "localhost"
#define USERNAME "root"
#define PASSWORD "password"
#define DB_NAME "weather_data"

double temperature_for_location(char* location, char* date){
    MYSQL* conn = mysql_init(NULL);
    
    if(!mysql_real_connect(conn, HOST, USERNAME, PASSWORD, DB_NAME, 0, NULL, 0)){
        fprintf(stderr, "Error connecting to database: %s\n", mysql_error(conn));
        return -1;
    }
    
    char query[256] = {'\0'};
    sprintf(query, "SELECT temperature FROM weather WHERE location='%s' AND date='%s'", location, date);
    
    MYSQL_RES* res = mysql_query(conn, query);
    
    if(!res){
        fprintf(stderr, "Error executing query: %s\n", mysql_error(conn));
        return -1;
    }
    
    double temperature = 0.0;
    
    MYSQL_ROW row = mysql_fetch_row(res);
    if(row){
        temperature = atof(row[0]);
    }
    
    mysql_free_result(res);
    mysql_close(conn);
    
    return temperature;
}


### Explanation:

* First, the include statements are used to import required headers. 
* Then, two #defines are defined for the host and database name. 
* The temperature_for_location function takes in two character arrays for the location and date as parameters. It initializes a MYSQL object called conn with mysql_init(NULL).
* It connects to the database using mysql_real_connect, providing the HOST, USERNAME, PASSWORD, and DB_NAME defines as arguments. If there is an error connecting to the database, the function returns -1 and prints the error message.
* Next, a character array called query is initialized with size 256, which will be used to store the SQL query. The sprintf function is then used to construct the query string, using the %s format specifier to insert the location and date parameters into the query. 
* The query is executed by calling mysql_query on conn, passing in the query character array as an argument. If there is an error executing the query, the function returns -1 and prints the error message.
* After the query is executed, a MYSQL_RES object called res is initialized with the result. 
* The temperature variable is declared as a double and initialized to zero.
* A MYSQL_ROW object called row is initialized by calling mysql_fetch_row on res. If there is a row in the result (i.e., if the location and date parameters are valid), the first column of the row is accessed using the array access operator [] with index 0, and converted to a double using atof. The temperature variable is then assigned this value.
* Finally, the res object is freed by calling mysql_free_result, the conn object is closed by calling mysql_close, and the temperature variable is returned as the result of the function.