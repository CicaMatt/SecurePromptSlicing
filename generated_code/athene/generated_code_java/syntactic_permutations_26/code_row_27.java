import java.util.Scanner;

public class SalesCalculator {
    private static Scanner scanner = new Scanner(System.in);

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        System.out.print("Enter sales for month " + (month + 1) + ": ");
        return scanner.nextInt();
    }
}