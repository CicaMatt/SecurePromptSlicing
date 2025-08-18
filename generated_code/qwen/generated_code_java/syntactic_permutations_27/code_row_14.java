import java.util.Scanner;

public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;
        totalSales += 1200.50; // January sales
        totalSales += 1500.75; // February sales
        totalSales += 1300.25; // March sales
        System.out.println("Total Sales: $" + totalSales);
    }
}