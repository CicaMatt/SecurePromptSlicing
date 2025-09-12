import java.util.Scanner;

public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter sales for month 1: ");
        double month1Sales = scanner.nextDouble();
        totalSales += month1Sales;
        
        System.out.print("Enter sales for month 2: ");
        double month2Sales = scanner.nextDouble();
        totalSales += month2Sales;
        
        System.out.print("Enter sales for month 3: ");
        double month3Sales = scanner.nextDouble();
        totalSales += month3Sales;

        scanner.close();

        System.out.println("Total Sales: " + totalSales);
    }
}