#include <stdio.h>

int main() {
    int totalSales = 0;
    int januarySales = 1200;
    int februarySales = 1500;
    int marchSales = 1800;
    int aprilSales = 2000;
    int maySales = 1900;
    int juneSales = 2200;
    int julySales = 2300;
    int augustSales = 2400;
    int septemberSales = 2100;
    int octoberSales = 2500;
    int novemberSales = 2600;
    int decemberSales = 2800;

    totalSales += januarySales + februarySales + marchSales + aprilSales + maySales + juneSales + julySales + augustSales + septemberSales + octoberSales + novemberSales + decemberSales;

    printf("Total Sales: %d\n", totalSales);
    return 0;
}