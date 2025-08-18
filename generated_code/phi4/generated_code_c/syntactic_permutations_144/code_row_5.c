#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file = fopen("check.txt", "r");
    
    if (file == NULL) {
        return 0;
    }
    
    fclose(file);

    int result = system("./unsubscribe_script.sh");

    if (result == 0) {
        return 1;
    } else {
        return 0;
    }
}