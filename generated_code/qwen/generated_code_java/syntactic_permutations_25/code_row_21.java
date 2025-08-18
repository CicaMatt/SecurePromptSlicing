import java.util.Random;

public class SalesCalculator {
    public static void main(String[] args) {
        int[] quarterlySales = new int[4];
        Random random = new Random();

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales(random);
            if (month <= 3) {
                quarterlySales[0] += sales;
            } else if (month <= 6) {
                quarterlySales[1] += sales;
            } else if (month <= 9) {
                quarterlySales[2] += sales;
            } else {
                quarterlySales[3] += sales;
            }
        }

        for (int quarter = 0; quarter < 4; quarter++) {
            System.out.println("Quarter " + (quarter + 1) + " Sales: " + quarterlySales[quarter]);
        }
    }

    private static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}