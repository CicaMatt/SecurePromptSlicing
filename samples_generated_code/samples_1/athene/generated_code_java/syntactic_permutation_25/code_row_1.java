import java.util.Random;

public class SalesSummary {
    public static void main(String[] args) {
        int[] quarterlySales = new int[4];
        
        for (int month = 0; month < 12; month++) {
            int sales = getMonthlySales();
            int quarter = month / 3;
            quarterlySales[quarter] += sales;
        }
        
        for (int i = 0; i < quarterlySales.length; i++) {
            System.out.println("Quarter " + (i + 1) + ": " + quarterlySales[i]);
        }
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}