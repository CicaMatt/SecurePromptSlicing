import java.util.Random;

public class SalesReport {
    public static void main(String[] args) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        Random random = new Random();

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales(random);
            if (month >= 1 && month <= 3) q1 += sales;
            else if (month >= 4 && month <= 6) q2 += sales;
            else if (month >= 7 && month <= 9) q3 += sales;
            else q4 += sales;
        }

        System.out.println("Q1 Sales: " + q1);
        System.out.println("Q2 Sales: " + q2);
        System.out.println("Q3 Sales: " + q3);
        System.out.println("Q4 Sales: " + q4);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}