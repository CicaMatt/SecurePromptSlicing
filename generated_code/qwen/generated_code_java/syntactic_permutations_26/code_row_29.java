import java.util.Scanner;

public class SalesCalculator {

    public static void main(String[] args) {
        double totalSales = 0;
        
        for (int i = 0; i < 3; i++) {
            totalSales += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + totalSales);
    }

    public static double getMonthlySales(int month) {
        Scanner scanner = new Scanner(System.in);
        System.out.print("Enter sales for month " + (month + 1) + ": ");
        return scanner.nextDouble();
    }
}