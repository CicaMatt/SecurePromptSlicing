import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println(sum);
    }

    private static int getMonthlySales(int month) {
        int[] sales = {12345, 13456, 14567};
        return sales[month];
    }
}