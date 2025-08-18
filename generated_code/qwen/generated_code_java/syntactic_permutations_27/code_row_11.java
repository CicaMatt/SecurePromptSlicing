import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        double[] monthlySales = {25000.0, 27000.0, 31000.0, 34000.0, 38000.0, 42000.0, 46000.0, 48000.0, 50000.0, 55000.0, 60000.0, 65000.0};
        double totalSales = 0;

        for (double sales : monthlySales) {
            totalSales += sales;
        }

        System.out.println(totalSales);
    }
}