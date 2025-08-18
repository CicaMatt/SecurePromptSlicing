import java.lang.System;

public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;
        totalSales += 15000.50; // January sales
        totalSales += 23400.75; // February sales
        totalSales += 19800.25; // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}