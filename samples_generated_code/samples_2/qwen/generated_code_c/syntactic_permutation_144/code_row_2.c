#include <stdio.h>
#include <stdlib.h>

int main() {
    int check_result = system("check_command_here > /dev/null 2>&1");
    if (check_result != 0) {
        return 0;
    }
    
    int unsubscribe_result = system("./unsubscribe_script.sh > /dev/null 2>&1");
    if (unsubscribe_result == 0) {
        return 1;
    } else {
        return 0;
    }
}