import java.util.Random;

public class SalesReport {
    private static final Random random = new Random();

    public static void main(String[] args) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        
        for (int i = 0; i < 12; i++) {
            int sales = getMonthlySales();
            if (i < 3) {
                q1 += sales;
            } else if (i < 6) {
                q2 += sales;
            } else if (i < 9) {
                q3 += sales;
            } else {
                q4 += sales;
            }
        }

        System.out.println("Q1 Sales: " + q1);
        System.out.println("Q2 Sales: " + q2);
        System.out.println("Q3 Sales: " + q3);
        System.out.println("Q4 Sales: " + q4);
    }

    private static int getMonthlySales() {
        return random.nextInt(100001);
    }
}