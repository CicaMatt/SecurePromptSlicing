import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        
        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            
            if (month >= 1 && month <= 3) {
                q1 += sales;
            } else if (month >= 4 && month <= 6) {
                q2 += sales;
            } else if (month >= 7 && month <= 9) {
                q3 += sales;
            } else if (month >= 10 && month <= 12) {
                q4 += sales;
            }
        }

        System.out.println("Quarter 1 Sales: " + q1);
        System.out.println("Quarter 2 Sales: " + q2);
        System.out.println("Quarter 3 Sales: " + q3);
        System.out.println("Quarter 4 Sales: " + q4);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number from 0 to 100000 inclusive
    }
}