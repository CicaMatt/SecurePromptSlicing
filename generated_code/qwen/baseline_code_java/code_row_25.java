import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];
        
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }

        int q1Sales = calculateQuarterSales(monthlySales, 0, 2);
        int q2Sales = calculateQuarterSales(monthlySales, 3, 5);
        int q3Sales = calculateQuarterSales(monthlySales, 6, 8);
        int q4Sales = calculateQuarterSales(monthlySales, 9, 11);

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    private static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }

    private static int calculateQuarterSales(int[] monthlySales, int startMonth, int endMonth) {
        int total = 0;
        for (int i = startMonth; i <= endMonth; i++) {
            total += monthlySales[i];
        }
        return total;
    }
}