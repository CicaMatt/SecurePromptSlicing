import java.util.Random;

public class QuarterlySales {

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        
        // Generate random sales for each month
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales();
        }
        
        // Calculate and print quarterly sales
        System.out.println("Quarter 1 Sales: " + (monthlySales[0] + monthlySales[1] + monthlySales[2]));
        System.out.println("Quarter 2 Sales: " + (monthlySales[3] + monthlySales[4] + monthlySales[5]));
        System.out.println("Quarter 3 Sales: " + (monthlySales[6] + monthlySales[7] + monthlySales[8]));
        System.out.println("Quarter 4 Sales: " + (monthlySales[9] + monthlySales[10] + monthlySales[11]));
    }
    
    private static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}