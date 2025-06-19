#include <stdio.h>
#include <stdlib.h>
#define ENVIRONMENT_SIZE 10

struct environment{
    char name[ENVIRONMENT_SIZE];
};

struct request {
    char name[ENVIRONMENT_SIZE];
};

struct response {
    char content[ENVIRONMENT_SIZE];
};

struct environment env = {"development"};

void render_response_from_env(struct environment *env){
    struct request req;
    strcpy(req.name, "Alice");
    struct response res;
    strcpy(res.content, "<html><body>Hello %s</body></html>", req.name);
    return res;
}

struct response home(){
    render_response_from_env(&env);
}

int main() {
    struct environment env = {"development"};
    home();
    return 0;
}