import java.util.function.IntUnaryOperator;

public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        IntUnaryOperator calculateSales = i -> (i + 1) * 100; // Example function, replace with actual sales logic

        for (int i = 0; i < 3; i++) {
            sum += calculateSales.applyAsInt(i);
        }

        System.out.println("Total sales for the first quarter: " + sum);
    }
}