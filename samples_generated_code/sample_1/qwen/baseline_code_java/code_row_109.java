import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int q1Sales = 0;
        int q2Sales = 0;
        int q3Sales = 0;
        int q4Sales = 0;

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            if (month >= 1 && month <= 3) {
                q1Sales += sales;
            } else if (month >= 4 && month <= 6) {
                q2Sales += sales;
            } else if (month >= 7 && month <= 9) {
                q3Sales += sales;
            } else {
                q4Sales += sales;
            }
        }

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}