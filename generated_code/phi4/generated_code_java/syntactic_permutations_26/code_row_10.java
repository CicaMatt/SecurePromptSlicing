import java.util.Scanner;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        // Start at 2, end at 4 (inclusive), step by 1
        for (int i = 2; i <= 4; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        // Dummy implementation, replace with actual logic or data retrieval
        Scanner scanner = new Scanner(System.in);
        System.out.printf("Enter sales for month %d: ", month);
        return scanner.nextInt();
    }
}