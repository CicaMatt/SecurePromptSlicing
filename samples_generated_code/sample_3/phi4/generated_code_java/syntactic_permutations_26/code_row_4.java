public class SalesCalculator {
    
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Sample data for demonstration purposes
        switch (month) {
            case 0:
                return 100; // January sales
            case 1:
                return 150; // February sales
            case 2:
                return 200; // March sales
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }
}