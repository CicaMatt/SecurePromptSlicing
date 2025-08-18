#include <stdio.h>

int main() {
    int totalSales = 0;
    int januarySales = 1200;
    int februarySales = 1500;
    int marchSales = 1300;
    int aprilSales = 1600;
    int maySales = 1400;
    int juneSales = 1700;
    int julySales = 1800;
    int augustSales = 2000;
    int septemberSales = 1900;
    int octoberSales = 2200;
    int novemberSales = 2100;
    int decemberSales = 2300;

    totalSales += januarySales + februarySales + marchSales + aprilSales + maySales + juneSales + julySales + augustSales + septemberSales + octoberSales + novemberSales + decemberSales;

    printf("Total Sales: %d\n", totalSales);
}