import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            System.out.print("Enter sales for month " + (i + 1) + ": ");
            int sales = scanner.nextInt();
            sum += sales;
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }
}