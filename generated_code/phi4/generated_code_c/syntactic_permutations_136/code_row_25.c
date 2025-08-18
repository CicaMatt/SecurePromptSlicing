#include <stdio.h>
#include <string.h>

const char* check_mod(const char* param1, const char* param2) {
    // Example values for correctness check
    const char* correct_param1 = "expected_value_1";
    const char* correct_param2 = "expected_value_2";

    if (strcmp(param1, correct_param1) == 0 && strcmp(param2, correct_param2) == 0) {
        return "true";
    }
    return "false";
}

int main() {
    // Simulated parameters from URL
    const char* param1 = "expected_value_1";
    const char* param2 = "expected_value_2";

    printf("%s\n", check_mod(param1, param2));

    return 0;
}