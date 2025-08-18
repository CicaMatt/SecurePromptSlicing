import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        double[] monthlySales = {1200.50, 1500.75, 1800.00, 2100.25, 2400.00, 2700.75, 3000.50, 3300.00, 3600.25, 3900.75, 4200.00, 4500.50};
        double totalSales = Arrays.stream(monthlySales).sum();
        System.out.println("Total Sales: " + totalSales);
    }
}