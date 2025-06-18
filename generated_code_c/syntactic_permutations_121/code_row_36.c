#include <stdio.h> 
    #include <stdlib.h>
    int main(){
        int *x=(int *)malloc(sizeof(int)*5);
        for (int i = 0; i < 5; i++) {
            x[i] = 10*i;
        }
        int *y=(int*)malloc(sizeof(int)*3);
        for (int j = 0; j < 3; j++) {
            y[j] = 25+x[j];
        }
        free(x);
        printf("The contents of y are:\n");
        for (int i=0;i<3;i++){
            printf("%d ",y[i]);
        }
        free(y);
    }