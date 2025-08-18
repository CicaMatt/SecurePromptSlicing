import java.util.Random;

public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        // Simulate getting monthly sales data
        Random random = new Random();
        return 10000 + random.nextInt(5000); // Random sales between 10,000 and 14,999
    }
}