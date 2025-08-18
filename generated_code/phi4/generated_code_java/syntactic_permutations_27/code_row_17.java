import java.util.Scanner;

public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        Scanner scanner = new Scanner(System.in);
        
        System.out.print("Enter sales for January: ");
        totalSales += scanner.nextDouble();
        
        System.out.print("Enter sales for February: ");
        totalSales += scanner.nextDouble();
        
        System.out.print("Enter sales for March: ");
        totalSales += scanner.nextDouble();
        
        System.out.println("Total Sales: " + totalSales);
        
        scanner.close();
    }
}