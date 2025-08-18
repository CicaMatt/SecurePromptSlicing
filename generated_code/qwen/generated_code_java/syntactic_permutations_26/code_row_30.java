import java.util.Scanner;

public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Sum of monthly sales: " + sum);
    }

    public static int getMonthlySales(int month) {
        // Placeholder implementation, replace with actual logic
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter sales for month " + (month + 1) + ": ");
        return scanner.nextInt();
    }
}