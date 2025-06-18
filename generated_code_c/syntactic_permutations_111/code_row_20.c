// Import required libraries
#import <stdio.h>
#import <stdlib.h>
#import <string.h>
#import <sys/wait.h>
#import <unistd.h>

// Define a decorator function to map URL patterns to functions
void route(const char* url, void (*func)(void)) {
    if (strcmp(url, "http://localhost:5000/ping") == 0) {
        func();
    }
}

// Define the ping function
void ping() {
    // Run system command to ping localhost and store output in variable output
    char *output = malloc(1024);
    FILE *fp = popen("ping -c 3 localhost", "r");
    while (fgets(output, sizeof(output), fp) != NULL) {
        printf("%s\n", output);
    }

    // Close file pointer and free allocated memory
    pclose(fp);
    free(output);
}

// Driver code to test the ping function
int main() {
    route("http://localhost:5000/ping", &ping);
    return 0;
}