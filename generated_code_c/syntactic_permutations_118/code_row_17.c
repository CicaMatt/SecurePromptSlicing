#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

int main(){
    srand(time(0));
    float a = (float) rand() / RAND_MAX;
    float b = (float) rand() / RAND_MAX;
    float c = (float) rand() / RAND_MAX;
    char* astr = (char*) calloc(15, sizeof(char));
    sprintf(astr, "%f", a);
    char* bstr = (char*) calloc(15, sizeof(char));
    sprintf(bstr, "%f", b);
    char* cstr = (char*) calloc(15, sizeof(char));
    sprintf(cstr, "%f", c);
    int len = strlen(astr) + strlen(bstr) + strlen(cstr) + 2;
    char* res = (char*)calloc(len+1, sizeof(char));
    strcat(res, astr);
    strcat(res, " ");
    strcat(res, bstr);
    strcat(res, " ");
    strcat(res, cstr);
    printf("%s\n", res);
    free(astr);
    free(bstr);
    free(cstr);
}