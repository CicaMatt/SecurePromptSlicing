import java.util.function.IntToDoubleFunction;

public class MonthlySalesCalculator {
    public static void main(String[] args) {
        double sum = 0;
        
        IntToDoubleFunction getMonthlySales = i -> {
            // Example implementation, replace with actual logic to fetch sales data
            switch (i) {
                case 0: return 10000.0; // January sales
                case 1: return 15000.0; // February sales
                case 2: return 20000.0; // March sales
                default: throw new IllegalArgumentException("Invalid month index");
            }
        };

        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales.applyAsDouble(i);
        }

        System.out.println("Total sales for the first quarter: " + sum);
    }
}