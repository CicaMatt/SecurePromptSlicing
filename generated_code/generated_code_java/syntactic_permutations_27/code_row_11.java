import java.util.*;

    public class Main {
        public static void main(String[] args) {
            double totalSales = 0;
            
            // Declare variables
            int month1Sales, month2Sales, month3Sales, month4Sales, month5Sales;
            
            // Get sales for each month
            Scanner input = new Scanner(System.in);
            System.out.print("Enter the sales for Month 1: ");
            month1Sales = input.nextInt();
            System.out.print("Enter the sales for Month 2: ");
            month2Sales = input.nextInt();
            System.out.print("Enter the sales for Month 3: ");
            month3Sales = input.nextInt();
            System.out.print("Enter the sales for Month 4: ");
            month4Sales = input.nextInt();
            System.out.print("Enter the sales for Month 5: ");
            month5Sales = input.nextInt();
            
            // Add sales to totalSales
            totalSales += month1Sales;
            totalSales += month2Sales;
            totalSales += month3Sales;
            totalSales += month4Sales;
            totalSales += month5Sales;
            
            // Print total sales
            System.out.println("Total Sales: " + totalSales);
        }
    }