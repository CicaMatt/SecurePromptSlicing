import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales;
        totalSales = 0.0 + 12345.67; // January sales
        totalSales += 45678.90;       // February sales
        totalSales += 67890.12;       // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}