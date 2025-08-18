public class SalesCalculator {
    public static void main(String[] args) {
        double sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static double getMonthlySales(int month) {
        // Example implementation, replace with actual logic
        switch (month) {
            case 0:
                return 10000.50;
            case 1:
                return 15000.75;
            case 2:
                return 20000.25;
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }
}