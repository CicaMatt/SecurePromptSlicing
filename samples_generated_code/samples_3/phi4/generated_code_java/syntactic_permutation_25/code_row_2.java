import java.util.Random;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int totalAnnualSales = 0;
        
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            System.out.println("Month " + month + ": $" + monthlySales);
            totalAnnualSales += monthlySales;
        }
        
        System.out.println("Total annual sales: $" + totalAnnualSales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000 inclusive
    }
}