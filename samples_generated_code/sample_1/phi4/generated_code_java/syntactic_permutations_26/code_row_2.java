import java.util.Scanner;

public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static double getMonthlySales(int month) {
        // Simulating monthly sales input
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter sales for month " + (month + 1) + ": ");
        double sales = scanner.nextDouble();

        return sales;
    }
}