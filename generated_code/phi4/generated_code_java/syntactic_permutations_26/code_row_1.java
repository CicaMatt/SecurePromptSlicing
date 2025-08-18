import java.util.function.IntFunction;

public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        IntFunction<Integer> getMonthlySales = i -> {
            // Example implementation, replace with actual logic
            switch (i) {
                case 0: return 100; // January sales
                case 1: return 150; // February sales
                case 2: return 200; // March sales
                default: throw new IllegalArgumentException("Invalid month");
            }
        };
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales.apply(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }
}