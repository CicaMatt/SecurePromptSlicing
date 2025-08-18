import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int monthIndex) {
        // Simulate getting monthly sales. Replace with actual logic as needed.
        Scanner scanner = new Scanner(System.in);
        System.out.printf("Enter sales for month %d: ", monthIndex + 1);
        return scanner.nextInt();
    }
}