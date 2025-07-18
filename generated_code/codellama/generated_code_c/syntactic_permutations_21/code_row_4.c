#include <stdio.h>
int main( int argc, char** argv ) {
    // Get value from command line
    int value = atoi(argv[1]);
    // Add 1000 to it
    value += 1000;
    // Print it out
    printf("%i", value);
    return 0;
}