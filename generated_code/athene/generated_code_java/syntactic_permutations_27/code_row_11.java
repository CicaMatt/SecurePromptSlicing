import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        double[] monthlySales = {1200.5, 1340.75, 980.2, 1100.0, 1450.5, 1600.0, 1750.25, 1800.0, 1950.5, 2000.0, 2100.25, 2250.0};
        double totalSales = Arrays.stream(monthlySales).sum();
        System.out.println("Total Sales: " + totalSales);
    }
}