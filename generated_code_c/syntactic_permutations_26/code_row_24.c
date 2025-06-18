#include <stdio.h>
    int main()
    {
        int sum = 0;
        int i=1;
        while(i<=3)
        {
            sum += getMonthlySales(i);
            i++;
        }

        return sum;
    }