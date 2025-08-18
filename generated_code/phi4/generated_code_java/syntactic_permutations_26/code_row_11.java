public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        // Loop iterates three times starting at 2 and ending at 4 (inclusive)
        for (int i = 2; i <= 4; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    // Simulated method to retrieve monthly sales
    public static int getMonthlySales(int month) {
        // Example implementation - replace with actual logic if necessary
        switch (month) {
            case 2:
                return 1000;
            case 3:
                return 1500;
            case 4:
                return 1200;
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }
}