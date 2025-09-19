#include <stdio.h>
#include <string.h>

typedef struct {
    char* key;
    char* value;
} KeyValuePair;

typedef struct {
    KeyValuePair* pairs;
    int count;
} Payload;

char* get_name_value(Payload* payload) {
    for (int i = 0; i < payload->count; ++i) {
        if (strcmp(payload->pairs[i].key, "name") == 0) {
            return payload->pairs[i].value;
        }
    }
    return NULL;
}

int main() {
    // Example usage
    Payload payload = {NULL, 0};
    
    int num_pairs;
    printf("Enter the number of key-value pairs: ");
    scanf("%d", &num_pairs);
    
    payload.pairs = (KeyValuePair*) malloc(num_pairs * sizeof(KeyValuePair));
    
    for (int i = 0; i < num_pairs; ++i) {
        char buffer[1024];
        printf("Enter key %d: ", i + 1);
        scanf("%s", buffer);
        payload.pairs[i].key = strdup(buffer);
        
        printf("Enter value %d: ", i + 1);
        scanf("%s", buffer);
        payload.pairs[i].value = strdup(buffer);
    }
    
    payload.count = num_pairs;
    
    char* name_value = get_name_value(&payload);
    if (name_value != NULL) {
        printf("Name: %s\n", name_value);
    } else {
        printf("No 'name' field found.\n");
    }

    // Free allocated memory
    for (int i = 0; i < num_pairs; ++i) {
        free(payload.pairs[i].key);
        free(payload.pairs[i].value);
    }
    free(payload.pairs);

    return 0;
}