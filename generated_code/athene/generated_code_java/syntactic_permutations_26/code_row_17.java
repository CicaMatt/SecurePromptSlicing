import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        int[] sales = {100, 200, 150};
        int sum = 0;
        for (int i = 0; i <= 2; i++) {
            sum += getSales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getSales(int month) {
        int[] sales = {100, 200, 150};
        return sales[month];
    }
}