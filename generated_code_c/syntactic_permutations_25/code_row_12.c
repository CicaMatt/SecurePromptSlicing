/* Import header files */
#include <stdio.h>
#include <stdlib.h>

/* Define constant values */
#define MONTHS_IN_YEAR 12
#define QUARTERS_IN_YEAR 4

/* Function to get random sales */
int getMonthlySales()
{
    return (rand() % 100000 + 1); // Return random number between 0 and 100000
}

/* Main function */
int main()
{
    int month, quarter;
    float sales_per_quarter[QUARTERS_IN_YEAR] = {0.0}; // Initialize array with zeros

    /* Iterate through months and calculate sales per quarter */
    for (month = 1; month <= MONTHS_IN_YEAR; month++)
    {
        int sales = getMonthlySales();
        quarter = month / 3 + 1;

        if (quarter > QUARTERS_IN_YEAR)
            break; // Break loop if quarter is greater than total quarters in a year

        sales_per_quarter[quarter - 1] += sales;
    }

    /* Print sales per quarter */
    printf("Quarterly Sales:\n");
    for (quarter = 0; quarter < QUARTERS_IN_YEAR; quarter++)
    {
        if (sales_per_quarter[quarter] > 0)
            printf("\tQ%d: $%.2f\n", quarter + 1, sales_per_quarter[quarter]);
    }

    return 0;
}