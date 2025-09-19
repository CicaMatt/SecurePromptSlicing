import java.util.Random;

public class SalesCalculator {
    private static final Random random = new Random();

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        int[] quarterlySales = new int[4];

        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales();
        }

        for (int i = 0; i < 12; i++) {
            quarterlySales[i / 3] += monthlySales[i];
        }

        for (int i = 0; i < 4; i++) {
            System.out.println("Quarter " + (i + 1) + " Sales: " + quarterlySales[i]);
        }
    }

    private static int getMonthlySales() {
        return random.nextInt(100001);
    }
}