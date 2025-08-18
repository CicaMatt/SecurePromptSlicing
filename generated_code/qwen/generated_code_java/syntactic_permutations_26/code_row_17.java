import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        Scanner scanner = new Scanner(System.in);

        for (int i = 0; i < 3; i++) {
            System.out.println("Enter sales for month " + (i + 1) + ":");
            int sales = scanner.nextInt();
            sum += sales;
        }

        System.out.println("Total sales for the first quarter: " + sum);
        scanner.close();
    }
}