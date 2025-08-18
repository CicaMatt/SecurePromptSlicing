import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        Random random = new Random();

        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }

        int q1Sales = monthlySales[0] + monthlySales[1] + monthlySales[2];
        int q2Sales = monthlySales[3] + monthlySales[4] + monthlySales[5];
        int q3Sales = monthlySales[6] + monthlySales[7] + monthlySales[8];
        int q4Sales = monthlySales[9] + monthlySales[10] + monthlySales[11];

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    private static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}