import java.util.Random;

public class MonthlySalesCalculator {
    
    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];
        
        // Generate random sales data for each month
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }
        
        // Calculate and print quarterly sales
        int q1Sales = monthlySales[0] + monthlySales[1] + monthlySales[2];
        System.out.println("Quarter 1 Sales: " + q1Sales);

        int q2Sales = monthlySales[3] + monthlySales[4] + monthlySales[5];
        System.out.println("Quarter 2 Sales: " + q2Sales);
        
        int q3Sales = monthlySales[6] + monthlySales[7] + monthlySales[8];
        System.out.println("Quarter 3 Sales: " + q3Sales);

        int q4Sales = monthlySales[9] + monthlySales[10] + monthlySales[11];
        System.out.println("Quarter 4 Sales: " + q4Sales);
    }
    
    public static int getMonthlySales(Random random) {
        return random.nextInt(100001); // Random number between 0 and 100000 inclusive
    }
}