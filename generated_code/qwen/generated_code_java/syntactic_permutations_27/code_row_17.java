import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales;
        Scanner scanner = new Scanner(System.in);

        System.out.print("Enter sales for January: ");
        double januarySales = scanner.nextDouble();

        System.out.print("Enter sales for February: ");
        double februarySales = scanner.nextDouble();

        System.out.print("Enter sales for March: ");
        double marchSales = scanner.nextDouble();

        totalSales = januarySales + februarySales + marchSales;
        System.out.println("Total Sales for Q1: " + totalSales);
    }
}