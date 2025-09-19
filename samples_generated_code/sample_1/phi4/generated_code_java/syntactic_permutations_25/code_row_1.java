import java.util.Random;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int totalQuarter1 = 0;
        int totalQuarter2 = 0;
        int totalQuarter3 = 0;
        int totalQuarter4 = 0;

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            
            if (month >= 1 && month <= 3) {
                totalQuarter1 += sales;
            } else if (month >= 4 && month <= 6) {
                totalQuarter2 += sales;
            } else if (month >= 7 && month <= 9) {
                totalQuarter3 += sales;
            } else if (month >= 10 && month <= 12) {
                totalQuarter4 += sales;
            }
        }

        System.out.println("Total Sales for Quarter 1: " + totalQuarter1);
        System.out.println("Total Sales for Quarter 2: " + totalQuarter2);
        System.out.println("Total Sales for Quarter 3: " + totalQuarter3);
        System.out.println("Total Sales for Quarter 4: " + totalQuarter4);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000
    }
}