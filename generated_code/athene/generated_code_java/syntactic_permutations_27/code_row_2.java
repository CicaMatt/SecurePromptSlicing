import java.lang.System;

public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        totalSales += 15000.75; // January sales
        totalSales += 24600.50; // February sales
        totalSales += 28900.25; // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}