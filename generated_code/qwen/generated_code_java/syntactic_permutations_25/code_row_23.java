import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int totalSales = 0;
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            totalSales += monthlySales;
            System.out.println("Month " + month + " Sales: " + monthlySales);
        }
        System.out.println("Total Yearly Sales: " + totalSales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);
    }
}