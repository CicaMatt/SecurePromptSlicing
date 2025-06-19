#include <stdio.h>

int main(int argc, char* argv[]) {
    int index;
    scanf("%d", &index);
    
    if (argc < index + 1) {
        printf("error\n");
        return 0;
    } else {
        printf("%s\n", argv[index]);
    }
}