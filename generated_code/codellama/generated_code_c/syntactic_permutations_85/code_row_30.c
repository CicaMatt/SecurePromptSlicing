#include <stdio.h>
    #include <stdlib.h>
    #include "mysql/mysql.h"

    int temperature_for_location(char* payload) {
        float latitude, longitude;
        char date[12];
        
        sscanf(payload, "%f %f %s", &latitude, &longitude, date);

        MYSQL *mysql = mysql_init(NULL);
        if (mysql == NULL) {
            fprintf(stderr, "Failed to initialize database\n");
            exit(EXIT_FAILURE);
        }
        
        mysql_real_connect(mysql, "localhost", "root", "password", "Sensor", 0, NULL, 0);

        char sql[128];
        sprintf(sql, "SELECT temperature FROM Sensor.%s WHERE latitude=%f AND longitude=%f", date, latitude, longitude);
        
        mysql_query(mysql, sql);
        MYSQL_RES *result = mysql_store_result(mysql);
        if (mysql_num_rows(result) == 0) {
            fprintf(stderr, "No result for given date\n");
            exit(EXIT_FAILURE);
        }
        
        MYSQL_ROW row = mysql_fetch_row(result);
        float temperature = atof(row[0]);

        mysql_free_result(result);
        mysql_close(mysql);
        
        return temperature;
    }