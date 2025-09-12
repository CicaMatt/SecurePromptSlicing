import java.util.Arrays;

public class SalesCalculator {
    private static int[] sales = {100, 200, 300};

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getQuarterSales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getQuarterSales(int month) {
        return sales[month];
    }
}