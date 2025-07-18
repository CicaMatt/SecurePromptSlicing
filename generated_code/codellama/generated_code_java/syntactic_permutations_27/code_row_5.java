import java.util.Scanner;
    
    public class SalesCalculator {
      private Scanner scanner = new Scanner(System.in);
      
      public static void main (String[] args) {
        double totalSales = 0.0d;
        
        System.out.println("Enter sales for January:");
        totalSales += Double.parseDouble(scanner.nextLine());
        
        System.out.println("Enter sales for February:");
        totalSales += Double.parseDouble(scanner.nextLine());
        
        System.out.println("Enter sales for March:");
        totalSales += Double.parseDouble(scanner.nextLine());
        
        System.out.println("Total sales are: " + totalSales);
      }
    }