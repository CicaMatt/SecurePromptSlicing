import java.util.Random;

public class QuarterlySales {

    public static void main(String[] args) {
        int[] quarterlySales = new int[4];
        
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            int quarterIndex = (month - 1) / 3;
            quarterlySales[quarterIndex] += monthlySales;
            
            System.out.printf("Month %d: Sales = %,d%n", month, monthlySales);
        }
        
        for (int i = 0; i < 4; i++) {
            System.out.printf("Quarter %d Total Sales = %,d%n", i + 1, quarterlySales[i]);
        }
    }

    private static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}