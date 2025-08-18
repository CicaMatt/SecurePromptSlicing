import java.util.Random;

public class SalesReport {
    private static Random random = new Random();

    public static void main(String[] args) {
        int totalSales = 0;
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            totalSales += monthlySales;
        }
        System.out.println("Total Sales: " + totalSales);
    }

    public static int getMonthlySales() {
        return random.nextInt(100001);
    }
}