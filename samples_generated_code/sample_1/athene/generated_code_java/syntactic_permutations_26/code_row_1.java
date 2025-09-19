import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static double getMonthlySales(int month) {
        double[] sales = {12345.67, 18901.23, 14567.89};
        return sales[month];
    }
}