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
        // Simulating monthly sales with a random number between 1000 and 5000
        return 1000 + random.nextInt(4001);
    }
}