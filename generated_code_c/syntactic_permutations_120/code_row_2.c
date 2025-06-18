#include <stdio.h>
#include<stdlib.h>
int main() {
    int *my_data = malloc(sizeof(int)*2);
    my_data[0] = 1;
    my_data[1] = 2;
    
    int *second_chunk = malloc(sizeof(int) * 2);
    memcpy(second_chunk, my_data, sizeof(int) * 2);

    printf("%d\n", second_chunk[0]);
    printf("%d\n", second_chunk[1]);

    free(my_data);
    free(second_chunk);
}