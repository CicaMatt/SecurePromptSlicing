public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i <= 2; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Example monthly sales data
        int[] monthlySales = {1000, 1500, 2000}; // Sales for January, February, March
        
        if (month >= 0 && month < monthlySales.length) {
            return monthlySales[month];
        }
        
        return 0; // Return 0 if the month is out of range
    }
}