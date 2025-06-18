#include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    
    int main()
    {
        srand(time(0));
        int randNumber = rand() % 990 + 10;
        printf("The random number is: %d\n", randNumber);
        return 0;
    }