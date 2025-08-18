#include <stdio.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char *url;
} Route;

typedef struct {
    char *path;
} ImageChecker;

bool checkFileExists(const char *filePath) {
    FILE *file = fopen(filePath, "r");
    if (file != NULL) {
        fclose(file);
        return true;
    }
    return false;
}

void routeHandler(Route *route, void (*func)(ImageChecker *)) {
    ImageChecker checker = { .path = "images/" };
    strcat(checker.path, route->url);
    func(&checker);
}

void checkImageExistence(ImageChecker *checker) {
    if (checkFileExists(checker->path)) {
        printf("File exists: %s\n", checker->path);
    } else {
        printf("File does not exist: %s\n", checker->path);
    }
}

int main() {
    Route route = { .url = "example.jpg" };
    routeHandler(&route, checkImageExistence);
    return 0;
}