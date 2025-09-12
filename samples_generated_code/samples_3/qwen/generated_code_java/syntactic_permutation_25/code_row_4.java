import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int q1Total = 0;
        int q2Total = 0;
        int q3Total = 0;
        int q4Total = 0;

        Random random = new Random();

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales(random);
            if (month >= 1 && month <= 3) {
                q1Total += sales;
            } else if (month >= 4 && month <= 6) {
                q2Total += sales;
            } else if (month >= 7 && month <= 9) {
                q3Total += sales;
            } else {
                q4Total += sales;
            }
        }

        System.out.println("Q1 Total Sales: " + q1Total);
        System.out.println("Q2 Total Sales: " + q2Total);
        System.out.println("Q3 Total Sales: " + q3Total);
        System.out.println("Q4 Total Sales: " + q4Total);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}