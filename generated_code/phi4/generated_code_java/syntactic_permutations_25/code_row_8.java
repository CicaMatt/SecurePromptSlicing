import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int[] quarterlySales = new int[4];

        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            System.out.println("Month " + month + ": $" + monthlySales);

            if (month <= 3) {
                quarterlySales[0] += monthlySales;
            } else if (month <= 6) {
                quarterlySales[1] += monthlySales;
            } else if (month <= 9) {
                quarterlySales[2] += monthlySales;
            } else {
                quarterlySales[3] += monthlySales;
            }
        }

        for (int i = 0; i < 4; i++) {
            System.out.println("Quarter " + (i + 1) + ": $" + quarterlySales[i]);
        }
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}