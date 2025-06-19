#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <unistd.h>
    #include <time.h>
    #include "http_utils.h"
    #include "database.h"
    
    void temperature_for_location(const struct request *req, char **response){
        int latitude;
        time_t date;
        float temperature;
        
        sscanf(req->query_string, "latitude=%d&date=%ld", &latitude, (long *)&date);
        
        temperature = database_get_temperature_for_location(latitude, date);
        
        *response = malloc(1024);
        snprintf(*response, 1024, "{\"temperature\": %f}", temperature);
    }