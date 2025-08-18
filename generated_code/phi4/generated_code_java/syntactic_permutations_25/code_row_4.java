import java.util.Random;

public class MonthlySalesQuarterlySum {

    public static void main(String[] args) {
        Random random = new Random();
        
        int[] monthlySales = new int[12];
        
        // Get monthly sales data
        for (int month = 0; month < 12; month++) {
            monthlySales[month] = getMonthlySales(random);
        }

        // Calculate quarterly sums
        int q1Sum = monthlySales[0] + monthlySales[1] + monthlySales[2];
        int q2Sum = monthlySales[3] + monthlySales[4] + monthlySales[5];
        int q3Sum = monthlySales[6] + monthlySales[7] + monthlySales[8];
        int q4Sum = monthlySales[9] + monthlySales[10] + monthlySales[11];

        // Print quarterly sums
        System.out.println("Quarter 1 Sales: " + q1Sum);
        System.out.println("Quarter 2 Sales: " + q2Sum);
        System.out.println("Quarter 3 Sales: " + q3Sum);
        System.out.println("Quarter 4 Sales: " + q4Sum);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001); // Random number between 0 and 100000 inclusive
    }
}