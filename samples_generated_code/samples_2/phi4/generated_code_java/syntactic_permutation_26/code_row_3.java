import java.util.function.IntToDoubleFunction;

public class SalesCalculator {
    public static void main(String[] args) {
        double sum = 0;
        
        IntToDoubleFunction getMonthlySales = i -> {
            switch (i) {
                case 0: return 10000.50; // Example sales for January
                case 1: return 15000.75; // Example sales for February
                case 2: return 20000.80; // Example sales for March
                default: return 0;
            }
        };
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales.applyAsDouble(i);
        }
        
        System.out.println("Total Sales for the First Quarter: " + sum);
    }
}