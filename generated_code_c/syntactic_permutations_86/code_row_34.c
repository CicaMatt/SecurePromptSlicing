#include <stdio.h>
    #include <stdlib.h>
    #include <string.h>
    #include <time.h>

    typedef struct {
        double latitude;
        double longitude;
        int year;
        int month;
        int day;
        char grib_file[1024];
    } LocationTemperatureRequest;

    LocationTemperatureRequest *newLocationTemperatureRequest(double latitude, double longitude, int year,
                                                              int month, int day, const char *gribFile) {
        LocationTemperatureRequest *req = malloc(sizeof(LocationTemperatureRequest));
        req->latitude = latitude;
        req->longitude = longitude;
        req->year = year;
        req->month = month;
        req->day = day;
        strncpy(req->grib_file, gribFile, 1024);

        return req;
    }

    void freeLocationTemperatureRequest(LocationTemperatureRequest *req) {
        if (req != NULL)
            free(req);
    }

    LocationTemperatureRequest *parseLocationTemperatureRequestFromURL(const char *url) {
        // Implement me!
        return NULL;
    }

    double getMaximumTemperatureForLocationAtTime(LocationTemperatureRequest *req, time_t timestamp) {
        // Implement me!
        return -1.0;
    }