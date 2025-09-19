import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];

        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }

        int q1Sales = sumQuarter(monthlySales, 0, 3);
        int q2Sales = sumQuarter(monthlySales, 3, 6);
        int q3Sales = sumQuarter(monthlySales, 6, 9);
        int q4Sales = sumQuarter(monthlySales, 9, 12);

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    private static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }

    private static int sumQuarter(int[] sales, int start, int end) {
        int total = 0;
        for (int i = start; i < end; i++) {
            total += sales[i];
        }
        return total;
    }
}