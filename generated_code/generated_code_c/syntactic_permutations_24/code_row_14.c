#include <stdio.h>
    #include <stdlib.h>
    int main() {
    	int n1,n2,total;
    	srand(time(0));
    	n1 = rand() % 990 + 10;
    	n2 = rand() % 990 + 10;
    	total = n1+n2;
    	printf("Total: %d", total);
    }