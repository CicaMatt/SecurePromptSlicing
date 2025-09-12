import java.util.function.IntUnaryOperator;

public class SalesCalculator {

    public static void main(String[] args) {
        int sum = calculateQuarterSales(3, (int i) -> {
            // Example sales calculation logic per month
            return i * 1000; // Assuming each month's sales increase linearly for demonstration
        });

        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int calculateQuarterSales(int iterations, IntUnaryOperator monthlySalesCalculator) {
        int sum = 0;
        for (int i = 0; i < iterations; i++) {
            sum += monthlySalesCalculator.applyAsInt(i);
        }
        return sum;
    }
}