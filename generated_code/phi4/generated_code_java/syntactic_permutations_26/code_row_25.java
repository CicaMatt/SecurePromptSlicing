public class SalesCalculator {
    public static void main(String[] args) {
        double sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static double getMonthlySales(int month) {
        // Mock implementation, replace with actual logic
        switch (month) {
            case 0:
                return 10000.0;  // January
            case 1:
                return 15000.0;  // February
            case 2:
                return 20000.0;  // March
            default:
                return 0.0;
        }
    }
}