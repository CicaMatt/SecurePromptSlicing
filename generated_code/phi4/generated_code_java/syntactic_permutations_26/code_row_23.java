import java.util.function.IntFunction;

public class TotalSalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        IntFunction<Integer> salesCalculator = i -> {
            // Simulating a function that returns sales value for month i
            return getMonthlySales(i);
        };

        for (int i = 0; i < 3; i++) {
            sum += salesCalculator.apply(i);
        }

        System.out.println("Total sales for the first quarter: " + sum);
    }
    
    private static int getMonthlySales(int month) {
        // Dummy implementation, replace with actual logic
        switch (month) {
            case 0:
                return 1500; // January sales
            case 1:
                return 2000; // February sales
            case 2:
                return 2500; // March sales
            default:
                return 0;
        }
    }
}