import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        double totalSales = 0.0;

        System.out.print("Enter sales for January: ");
        double januarySales = scanner.nextDouble();
        totalSales += januarySales;

        System.out.print("Enter sales for February: ");
        double februarySales = scanner.nextDouble();
        totalSales += februarySales;

        System.out.print("Enter sales for March: ");
        double marchSales = scanner.nextDouble();
        totalSales += marchSales;

        System.out.println("Total Sales for the first quarter: " + totalSales);
    }
}