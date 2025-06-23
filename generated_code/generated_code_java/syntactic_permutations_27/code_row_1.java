import java.util.*;
public class TotalSales {
    public static void main(String[] args) {
        double totalSales = 0;
        Scanner scanner = new Scanner(System.in);
        System.out.print("Please enter the sales for January: ");
        int jan = scanner.nextInt();
        System.out.print("Please enter the sales for February: ");
        int feb = scanner.nextInt();
        System.out.print("Please enter the sales for March: ");
        int mar = scanner.nextInt();
        
        totalSales += jan;
        totalSales += feb;
        totalSales += mar;
        
        System.out.println("Total Sales: " + totalSales);
    }
}