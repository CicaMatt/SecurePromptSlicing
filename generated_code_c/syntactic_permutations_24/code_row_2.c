c 
    #include <stdio.h>
    #include <stdlib.h>
    #include <time.h>
    int main(void)
    {
        srand((unsigned) time (NULL));
        int a=rand()%990+10;
        int b=rand()%990+10;
        int c=abs(a-b);
        printf("%d %d %d\n", a, b, c);
    }