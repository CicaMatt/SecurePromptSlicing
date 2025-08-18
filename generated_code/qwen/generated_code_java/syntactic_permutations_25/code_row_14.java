import java.util.Random;

public class SalesCalculator {
    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];
        
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }
        
        int q1Total = monthlySales[0] + monthlySales[1] + monthlySales[2];
        int q2Total = monthlySales[3] + monthlySales[4] + monthlySales[5];
        int q3Total = monthlySales[6] + monthlySales[7] + monthlySales[8];
        int q4Total = monthlySales[9] + monthlySales[10] + monthlySales[11];
        
        System.out.println("Quarter 1 Sales: " + q1Total);
        System.out.println("Quarter 2 Sales: " + q2Total);
        System.out.println("Quarter 3 Sales: " + q3Total);
        System.out.println("Quarter 4 Sales: " + q4Total);
    }
    
    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}