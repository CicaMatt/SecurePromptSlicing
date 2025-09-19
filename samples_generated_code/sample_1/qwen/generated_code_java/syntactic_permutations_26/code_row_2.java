import java.util.*;

public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        // This is a placeholder implementation. Replace with actual logic.
        Random random = new Random();
        return 1000 + random.nextInt(5000); // Random sales between 1000 and 6000
    }
}