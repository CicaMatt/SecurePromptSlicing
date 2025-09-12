import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getSalesForMonth(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getSalesForMonth(int month) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter sales for month " + (month + 1) + ": ");
        return scanner.nextInt();
    }
}