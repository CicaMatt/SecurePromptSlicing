import java.util.Random;

public class SalesCalculator {
    private static final Random random = new Random();

    public static void main(String[] args) {
        int q1Sales = 0, q2Sales = 0, q3Sales = 0, q4Sales = 0;

        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            switch ((month - 1) / 3) {
                case 0:
                    q1Sales += monthlySales;
                    break;
                case 1:
                    q2Sales += monthlySales;
                    break;
                case 2:
                    q3Sales += monthlySales;
                    break;
                case 3:
                    q4Sales += monthlySales;
                    break;
            }
        }

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    private static int getMonthlySales() {
        return random.nextInt(100001);
    }
}