import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int totalSales = 0;
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            totalSales += monthlySales;
        }
        System.out.println("Total sales for the year: " + totalSales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 (inclusive) and 100001 (exclusive)
    }
}