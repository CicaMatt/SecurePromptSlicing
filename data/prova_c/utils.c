#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *global_ptr;

void use_after_free() {
    char *data = (char *)malloc(20);
    strcpy(data, "hello world");
    free(data);
    printf("Use after free: %s\n", data); // USE AFTER FREE
}

void memory_leak() {
    global_ptr = malloc(100);
    strcpy(global_ptr, "This is a leak");
    // Memory not freed
}
