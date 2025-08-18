public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Placeholder implementation, replace with actual logic
        switch (month) {
            case 0:
                return 1000; // Example sales for January
            case 1:
                return 1500; // Example sales for February
            case 2:
                return 1200; // Example sales for March
            default:
                return 0;
        }
    }
}