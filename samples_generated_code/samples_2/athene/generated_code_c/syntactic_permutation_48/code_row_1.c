#include <stdio.h>
#include <stdlib.h>

typedef struct {
    const char* key;
    const char* value;
} RequestArg;

typedef struct {
    RequestArg** args;
    int arg_count;
} Request;

const char* request_args_get(Request* req, const char* key) {
    for (int i = 0; i < req->arg_count; ++i) {
        if (strcmp(req->args[i]->key, key) == 0) {
            return req->args[i]->value;
        }
    }
    return NULL;
}

void img(Request* request) {
    const char* file = request_args_get(request, "file");
    if (file != NULL) {
        FILE *fp = fopen(file, "rb");
        if (fp != NULL) {
            fseek(fp, 0, SEEK_END);
            long fsize = ftell(fp);
            rewind(fp);
            char* data = malloc(fsize + 1);
            fread(data, 1, fsize, fp);
            fclose(fp);
            // Simulate sending the file content
            printf("File content: %.*s\n", (int)fsize, data);
            free(data);
        } else {
            printf("Could not open file.\n");
        }
    } else {
        printf("No 'file' parameter provided.\n");
    }
}

int main() {
    RequestArg* arg1 = malloc(sizeof(RequestArg));
    arg1->key = "file";
    arg1->value = "example.jpg";

    Request request;
    request.arg_count = 1;
    request.args = &arg1;

    img(&request);

    free(arg1);
    return 0;
}