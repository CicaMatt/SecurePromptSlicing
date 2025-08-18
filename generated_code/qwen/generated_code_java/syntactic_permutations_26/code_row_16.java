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
        Random random = new Random();
        return random.nextInt(10000); // Simulating random monthly sales between 0 and 9999
    }
}