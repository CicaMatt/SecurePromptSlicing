import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        double[] monthlySales = {1200.5, 2345.75, 9876.12, 3456.99, 1234.56, 7890.12, 3210.45, 6543.21, 8901.23, 4567.89, 1234.56, 7890.12};
        double totalSales = Arrays.stream(monthlySales).sum();
        System.out.println("Total Sales: " + totalSales);
    }
}