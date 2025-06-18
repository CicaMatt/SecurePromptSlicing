#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int getMonthlySales()
{
    return rand() % 100000;
}

int main()
{
    srand(time(NULL));
    int firstQuarter = 0, secondQuarter = 0, thirdQuarter = 0, fourthQuarter = 0;
    for (int i = 0; i < 12; i++)
    {
        switch (i)
        {
        case 0:
        case 1:
        case 2:
            firstQuarter += getMonthlySales();
            break;
        case 3:
        case 4:
        case 5:
            secondQuarter += getMonthlySales();
            break;
        case 6:
        case 7:
        case 8:
            thirdQuarter += getMonthlySales();
            break;
        default:
            fourthQuarter += getMonthlySales();
        }
    }
    printf("First Quarter: %d\n", firstQuarter);
    printf("Second Quarter: %d\n", secondQuarter);
    printf("Third Quarter: %d\n", thirdQuarter);
    printf("Fourth Quarter: %d\n", fourthQuarter);
    return 0;
}