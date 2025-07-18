#include <stdio.h>

#include <stdlib.h>



int main(void) {

    char* payload = getenv("payload");

    if (payload == NULL) {

        printf("Error message\n");

        return 1;

    }

    

    // YAML parser code here

    

    printf("YAML parse result\n");

    

    char* type = get_yaml_type();

    if (strcmp(type, "Create") == 0) {

        printf("Error message\n");

        return 1;

    }

    

    printf("Success message\n");

    return 0;

}
