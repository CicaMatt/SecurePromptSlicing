#include <stdlib.h>
    
    float random_float(){
        return (float)rand()/(float)(RAND_MAX);
    }
    
    int main(){
    
        float a = random_float();
        float b = random_float();
        float c = random_float();
        
        char *str_a = (char*)malloc(sizeof(char)*20);
        sprintf(str_a, "%f", a);
    
        char *str_b = (char*)malloc(sizeof(char)*20);
        sprintf(str_b, "%f", b);
        
        char *str_c = (char*)malloc(sizeof(char)*20);
        sprintf(str_c, "%f", c);
    }