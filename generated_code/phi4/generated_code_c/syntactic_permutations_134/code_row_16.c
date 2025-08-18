#include <stdio.h>
#include <string.h>

char* escape(const char* input) {
    static char output[256];
    const char *special_chars = "<>&\"";
    char *out_ptr = output;
    
    while (*input) {
        if (strchr(special_chars, *input)) {
            switch(*input) {
                case '<': strcpy(out_ptr, "&lt;"); out_ptr += 4; break;
                case '>': strcpy(out_ptr, "&gt;"); out_ptr += 4; break;
                case '&': strcpy(out_ptr, "&amp;"); out_ptr += 5; break;
                case '"': strcpy(out_ptr, "&quot;"); out_ptr += 6; break;
            }
        } else {
            *out_ptr++ = *input;
        }
        input++;
    }
    *out_ptr = '\0';
    return output;
}

void hello(const char* username) {
    printf("Hello %s\n", escape(username));
}

int main(int argc, char *argv[]) {
    if (argc != 2 || strcmp(argv[1], "/hello/") != 0) {
        printf("Usage: %s /hello/username\n", argv[0]);
        return 1;
    }

    const char* username = "";
    if (argc > 2) {
        username = argv[1] + strlen("/hello/");
    }
    
    hello(username);
    return 0;
}