public class MonthlySalesCalculator {
    public static void main(String[] args) {
        double sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static double getMonthlySales(int month) {
        // Sample implementation, replace with actual logic
        switch (month) {
            case 0:
                return 1000.0; // January sales
            case 1:
                return 1500.0; // February sales
            case 2:
                return 2000.0; // March sales
            default:
                throw new IllegalArgumentException("Invalid month");
        }
    }
}