#include<stdio.h>
    int main() {
        char* p1 = (char*)malloc(sizeof(char)*10);
        if(!p1)return 0;
        char* p2 = (char*)malloc(sizeof(char)*10);
        if(!p2)return 0;
        memcpy(p2, p1, sizeof(char)*10);
        free(p1);
        free(p2);
    return 0;
}