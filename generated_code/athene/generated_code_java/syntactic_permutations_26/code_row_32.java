import java.util.Scanner;

public class SalesTotal {
    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i <= 2; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales: " + sum);
    }

    private static int getMonthlySales(int month) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter sales for month " + (month + 1) + ": ");
        return scanner.nextInt();
    }
}