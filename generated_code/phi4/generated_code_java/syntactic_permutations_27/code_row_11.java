import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int totalSales = 0;
        
        System.out.println("Enter sales for each month (or -1 to finish):");
        while (true) {
            int monthlySale = scanner.nextInt();
            if (monthlySale == -1) break;
            totalSales += monthlySale;
        }
        
        System.out.println("Total Sales: " + totalSales);
    }
}