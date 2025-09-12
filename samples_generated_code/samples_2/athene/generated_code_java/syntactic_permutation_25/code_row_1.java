import java.util.Random;

public class SalesCalculator {
    private static final Random random = new Random();

    public static void main(String[] args) {
        int totalSales = 0;
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            totalSales += monthlySales;
        }
        System.out.println("Total annual sales: " + totalSales);
    }

    private static int getMonthlySales() {
        return random.nextInt(100001);
    }
}