import java.util.Random;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int totalSales = 0;
        
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            System.out.println("Month " + month + ": $" + monthlySales);
            totalSales += monthlySales;
        }
        
        System.out.println("Total sales for the year: $" + totalSales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000 inclusive
    }
}