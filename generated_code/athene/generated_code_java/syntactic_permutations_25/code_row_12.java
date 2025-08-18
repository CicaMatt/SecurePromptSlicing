import java.util.Random;

public class SalesReport {
    public static void main(String[] args) {
        int q1 = getQuarterlySales(1, 4);
        int q2 = getQuarterlySales(5, 7);
        int q3 = getQuarterlySales(8, 10);
        int q4 = getQuarterlySales(11, 12);

        System.out.println("Q1 Sales: " + q1);
        System.out.println("Q2 Sales: " + q2);
        System.out.println("Q3 Sales: " + q3);
        System.out.println("Q4 Sales: " + q4);
    }

    private static int getQuarterlySales(int startMonth, int endMonth) {
        int total = 0;
        for (int i = startMonth; i <= endMonth; i++) {
            total += getMonthlySales(i);
        }
        return total;
    }

    private static int getMonthlySales(int month) {
        Random random = new Random();
        return random.nextInt(100001);
    }
}