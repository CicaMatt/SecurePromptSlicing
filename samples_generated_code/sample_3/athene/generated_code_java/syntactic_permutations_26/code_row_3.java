import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        int[] sales = {100, 200, 300};
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getSales(i, sales);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getSales(int index, int[] sales) {
        return sales[index];
    }
}