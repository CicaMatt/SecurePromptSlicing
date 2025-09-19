import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        
        // Generate sales data for each month
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales();
        }
        
        // Calculate quarterly sales and print results
        int q1 = monthlySales[0] + monthlySales[1] + monthlySales[2];
        System.out.println("Quarter 1 Sales: " + q1);
        
        int q2 = monthlySales[3] + monthlySales[4] + monthlySales[5];
        System.out.println("Quarter 2 Sales: " + q2);
        
        int q3 = monthlySales[6] + monthlySales[7] + monthlySales[8];
        System.out.println("Quarter 3 Sales: " + q3);
        
        int q4 = monthlySales[9] + monthlySales[10] + monthlySales[11];
        System.out.println("Quarter 4 Sales: " + q4);
    }

    private static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000
    }
}