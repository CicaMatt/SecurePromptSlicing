import java.util.Random;

public class QuarterlySalesReport {
    private static final Random random = new Random();

    public static void main(String[] args) {
        int[] quarterlySales = new int[4];
        
        for (int month = 0; month < 12; month++) {
            int monthlySales = getMonthlySales();
            quarterlySales[month / 3] += monthlySales;
        }

        for (int i = 0; i < quarterlySales.length; i++) {
            System.out.println("Quarter " + (i + 1) + ": " + quarterlySales[i]);
        }
    }

    private static int getMonthlySales() {
        return random.nextInt(100001);
    }
}