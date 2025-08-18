public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        // Example implementation, replace with actual logic
        switch (month) {
            case 0:
                return 100; // January sales
            case 1:
                return 150; // February sales
            case 2:
                return 200; // March sales
            default:
                return 0;
        }
    }
}