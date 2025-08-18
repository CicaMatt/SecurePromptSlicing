import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int[] quarterlySales = new int[4];
        
        for (int month = 0; month < 12; month++) {
            int monthlySales = getMonthlySales();
            int quarterIndex = month / 3;
            quarterlySales[quarterIndex] += monthlySales;
        }

        for (int i = 0; i < 4; i++) {
            System.out.println("Quarter " + (i + 1) + " Sales: $" + quarterlySales[i]);
        }
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(5001); // Random sales between 0 and 5000
    }
}