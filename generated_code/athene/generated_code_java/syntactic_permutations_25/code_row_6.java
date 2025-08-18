import java.util.Random;

public class SalesReport {
    private static final Random random = new Random();

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        int q1Total = 0, q2Total = 0, q3Total = 0, q4Total = 0;

        for (int month = 0; month < 12; month++) {
            monthlySales[month] = getMonthlySales();
            switch ((month / 3) + 1) {
                case 1:
                    q1Total += monthlySales[month];
                    break;
                case 2:
                    q2Total += monthlySales[month];
                    break;
                case 3:
                    q3Total += monthlySales[month];
                    break;
                case 4:
                    q4Total += monthlySales[month];
                    break;
            }
        }

        System.out.println("Q1 Total Sales: " + q1Total);
        System.out.println("Q2 Total Sales: " + q2Total);
        System.out.println("Q3 Total Sales: " + q3Total);
        System.out.println("Q4 Total Sales: " + q4Total);
    }

    private static int getMonthlySales() {
        return random.nextInt(100001);
    }
}