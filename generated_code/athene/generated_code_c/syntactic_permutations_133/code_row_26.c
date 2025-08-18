#include <stdio.h>

typedef struct {
    // Web application properties and methods would go here
} WebApplication;

WebApplication app;

#define route(url) void handle_##url()

route(/)
{
    printf("Hello, World!\n");
}