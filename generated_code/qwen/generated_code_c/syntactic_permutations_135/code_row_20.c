#include <stdio.h>
#include <stdbool.h>

// Assuming the form data is passed as arguments to the function
bool check_mod(int value1, int value2) {
    // Example condition: Check if both values are positive
    if (value1 > 0 && value2 > 0) {
        return true;
    } else {
        return false;
    }
}

int main() {
    // Simulating form input
    int input1 = 5;
    int input2 = 10;

    bool result = check_mod(input1, input2);

    if (result) {
        printf("Values are correct.\n");
    } else {
        printf("Values are not correct.\n");
    }

    return 0;
}