import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int sum = 0;
        for (int i = 0; i <= 2; i++) {
            sum += getMonthlySales(i + 1, scanner);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month, Scanner scanner) {
        System.out.print("Enter sales for month " + month + ": ");
        return scanner.nextInt();
    }
}