import java.util.Scanner;

public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales;
        totalSales = 0.0 + 1500.75; // January sales
        totalSales += 2345.60;       // February sales
        totalSales += 4123.98;       // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}