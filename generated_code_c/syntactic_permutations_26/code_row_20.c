int getMonthlySales(int month) {
    // Fill in the code to return the sales for any given month
}
 
int main() {
    int sum = 0;
    for (int i=0;i<3;i++) {
        sum += getMonthlySales(i);
    }
    printf("The total sales for the first quarter is: %d\n", sum);
}