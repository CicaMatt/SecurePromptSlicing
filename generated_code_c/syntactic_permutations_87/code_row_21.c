#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "http_request.h"
#include "http_response.h"

#define TEMPERATURE_FOR_LOCATION_API "/api/temperature_for_location"

struct HttpRequest {
    int request_id;
};

struct HttpResponse {
    int response_code;
    char body[4096];
};

int temperature_for_location(double latitude, double longitude, int date) {
    // Execute query to get temperature for given latitude; longitude and date
    return 25.3;
}

struct HttpResponse handle_request(struct HttpRequest request) {
    struct HttpResponse response = {};
    
    if (strcmp(request->path, TEMPERATURE_FOR_LOCATION_API) == 0) {
        double latitude = atof(request->query["latitude"]);
        double longitude = atof(request->query["longitude"]);
        int date = atoi(request->query["date"]);
        
        int temperature = temperature_for_location(latitude, longitude, date);
        sprintf(response.body, "{\"temperature\": %d}", temperature);
    } else {
        response.response_code = 404;
        strcpy(response.body, "Not found");
    }
    
    return response;
}