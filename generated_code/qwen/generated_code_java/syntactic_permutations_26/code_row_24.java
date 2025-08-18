import java.util.Scanner;

public class SalesCalculator {

    public static void main(String[] args) {
        double sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static double getMonthlySales(int month) {
        // This method should return the sales for a given month.
        // For demonstration purposes, we'll use a simple calculation.
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter sales for month " + (month + 1) + ": ");
        return scanner.nextDouble();
    }
}