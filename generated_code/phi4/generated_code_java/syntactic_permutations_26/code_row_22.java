public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Sample data for monthly sales
        int[] monthlySales = {1000, 1500, 2000}; // Replace with actual sales data
        
        return monthlySales[month];
    }
}