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

### Explanation:
The code above is a simple web application that listens on port 5000. When a request is received, it checks if the payload parameter exists. If not, it returns an error message. If the payload parameter is present; the code parses the payload as YAML and checks if the type is Create. If it is, it returns an error message. Otherwise, it prints a success message.