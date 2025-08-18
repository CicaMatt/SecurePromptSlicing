import java.util.Arrays;

public class SalesCalculator {
    public static void main(String[] args) {
        double[] monthlySales = {25000.0, 27000.0, 31000.0, 34000.0, 38000.0, 42000.0, 45000.0, 47000.0, 50000.0, 55000.0, 60000.0, 65000.0};
        double totalSales = Arrays.stream(monthlySales).sum();
        System.out.println(totalSales);
    }
}