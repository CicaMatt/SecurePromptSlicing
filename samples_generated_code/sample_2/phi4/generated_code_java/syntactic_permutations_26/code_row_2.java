import java.util.function.IntFunction;

public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        IntFunction<Integer> getMonthlySales = (i) -> {
            // Simulated monthly sales values, replace with actual logic if needed
            switch (i) {
                case 0: return 1000; // Sales for January
                case 1: return 1500; // Sales for February
                case 2: return 1200; // Sales for March
                default: return 0;
            }
        };
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales.apply(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }
}