#include <stdio.h>  // for printf()
    #include <stdlib.h> // for exit(), perror()

    int main(void) {
        float latitude, longitude;
        char date[10];
        int temperature;
        const char* url = "/api/temperature_for_location";
        const char* query = "SELECT temperature FROM weather WHERE latitude=? AND longitude=? AND date=?";

        printf("Enter latitude: ");
        scanf("%f", &latitude);
        printf("Enter longitude: ");
        scanf("%f", &longitude);
        printf("Enter date (YYYY-MM-DD): ");
        scanf("%9s", date);

        // Connect to database and execute query here...

        // Print result here...

        return 0;
    }