#include <stdio.h>
    #include <mysql/mysql.h>
    
    int main() {
        float latitude, longitude, max_temp;
        int year, month, day;
        char grib_file[256];
        
        // Get data from request
        latitude = get_float_from_request("lat");
        longitude = get_float_from_request("lon");
        sscanf(get_string_from_request("date"), "%d-%d-%d", &year, &month, &day);
        strcpy(grib_file, get_string_from_request("grib"));
        
        // Connect to MySQL database
        MYSQL *conn = mysql_init(NULL);
        if (mysql_real_connect(conn, "localhost", "root", "password", "weather", 0, NULL, 0)) {
            char query[256];
            
            // Build SQL query
            sprintf(query, "SELECT max_temp FROM weather WHERE latitude=%f AND longitude=%f AND year=%d AND month=%d AND day=%d AND grib_file='%s';", latitude, longitude, year, month, day, grib_file);
            
            // Execute query and get result
            if (mysql_query(conn, query)) {
                fprintf(stderr, "MySQL query error: %s\n", mysql_error(conn));
                return 1;
            }
            
            MYSQL_RES *result = mysql_store_result(conn);
            if (result) {
                while (MYSQL_ROW row = mysql_fetch_row(result)) {
                    max_temp = atof(row[0]);
                    printf("Maximum temperature: %.2f\n", max_temp);
                }
            } else {
                fprintf(stderr, "MySQL result error: %s\n", mysql_error(conn));
                return 1;
            }
        } else {
            fprintf(stderr, "MySQL connection error: %s\n", mysql_error(conn));
            return 1;
        }
        
        return 0;
    }