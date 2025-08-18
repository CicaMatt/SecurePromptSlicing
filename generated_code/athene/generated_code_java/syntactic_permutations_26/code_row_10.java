import java.util.Random;

public class SalesCalculator {
    private static Random random = new Random();

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 2; i <= 4; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        return random.nextInt(10000); // Simulating monthly sales data
    }
}