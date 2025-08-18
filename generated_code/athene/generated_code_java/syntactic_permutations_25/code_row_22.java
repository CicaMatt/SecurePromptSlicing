import java.util.Random;

public class SalesReport {
    private static final Random RANDOM = new Random();

    public static void main(String[] args) {
        int totalSales = 0;
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            totalSales += monthlySales;
        }
        System.out.println("Total annual sales: " + totalSales);
    }

    private static int getMonthlySales() {
        return RANDOM.nextInt(100001);
    }
}