import java.util.function.IntToDoubleFunction;

public class SalesCalculator {

    public static void main(String[] args) {
        double sum = 0;
        
        IntToDoubleFunction getMonthlySales = i -> {
            // This is a placeholder implementation.
            // Replace the return value with actual logic to retrieve sales for month i.
            switch (i) {
                case 0: return 10000.0; // January
                case 1: return 15000.0; // February
                case 2: return 20000.0; // March
                default: throw new IllegalArgumentException("Invalid month index");
            }
        };

        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales.applyAsDouble(i);
        }

        System.out.println("Total sales for the first quarter: " + sum);
    }
}