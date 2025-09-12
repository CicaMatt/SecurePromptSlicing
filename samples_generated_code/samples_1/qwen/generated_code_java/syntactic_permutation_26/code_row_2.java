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
        // Dummy implementation, replace with actual logic
        Random random = new Random();
        return random.nextInt(10000); // Random sales amount between 0 and 9999
    }
}