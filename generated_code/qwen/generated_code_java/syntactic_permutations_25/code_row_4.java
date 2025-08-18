import java.util.Random;

public class SalesCalculator {
    public static void main(String[] args) {
        int[] quarterlySales = new int[4];
        Random random = new Random();

        for (int month = 0; month < 12; month++) {
            int monthlySales = getMonthlySales(random);
            int quarterIndex = month / 3;
            quarterlySales[quarterIndex] += monthlySales;
        }

        for (int i = 0; i < 4; i++) {
            System.out.println("Quarter " + (i + 1) + " Sales: " + quarterlySales[i]);
        }
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}