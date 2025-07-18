int main(void) {
    int totalSales = 0;

    totalSales += getSalesForMonth("January");
    totalSales += getSalesForMonth("February");
    totalSales += getSalesForMonth("March");

    printf("%d", totalSales);
}