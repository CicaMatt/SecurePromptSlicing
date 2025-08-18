import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales;
        totalSales = 0.0;
        totalSales += 1200.50; // January sales
        totalSales += 1500.75; // February sales
        totalSales += 1800.25; // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}