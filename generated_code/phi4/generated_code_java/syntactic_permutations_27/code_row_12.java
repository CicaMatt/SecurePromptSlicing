import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        
        int totalSales = 0;
        int numberOfMonths = 12; // Assuming a year's worth of sales data
        
        for (int i = 1; i <= numberOfMonths; i++) {
            System.out.printf("Enter the sales for month %d: ", i);
            int salesForMonth = scanner.nextInt();
            totalSales += salesForMonth;
        }
        
        System.out.println("Total Sales: " + totalSales);
        
        scanner.close();
    }
}