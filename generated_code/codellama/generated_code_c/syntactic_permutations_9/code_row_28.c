#include<stdio.h>
    #include<stdlib.h>
    int main(int argc, char *argv[]) {
        int index;
        scanf("%d", &index);
        if (argc - 1 >= index)
            printf("%s\n", argv[index + 1]);
        else
            printf("Index out of range!\n");
        return 0;
    }