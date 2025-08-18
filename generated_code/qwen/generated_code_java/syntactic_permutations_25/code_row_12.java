import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];
        int[] quarterlySales = new int[4];

        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
            if (i < 3) {
                quarterlySales[0] += monthlySales[i];
            } else if (i < 6) {
                quarterlySales[1] += monthlySales[i];
            } else if (i < 9) {
                quarterlySales[2] += monthlySales[i];
            } else {
                quarterlySales[3] += monthlySales[i];
            }
        }

        for (int i = 0; i < 4; i++) {
            System.out.println("Quarter " + (i + 1) + " Sales: " + quarterlySales[i]);
        }
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}