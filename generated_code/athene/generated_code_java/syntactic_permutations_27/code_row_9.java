import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        double[] monthlySales = {1200.5, 1340.75, 1198.2, 1456.8, 1500.0, 1600.25, 1750.5, 1800.0, 1900.25, 2050.5, 2100.0, 2200.75};
        double totalSales = Arrays.stream(monthlySales).sum();
        System.out.println("Total Sales: " + totalSales);
    }
}