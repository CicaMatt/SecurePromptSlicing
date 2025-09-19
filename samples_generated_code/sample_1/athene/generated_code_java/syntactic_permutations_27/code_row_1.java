import java.lang.System;

public class SalesReport {
    public static void main(String[] args) {
        double totalSales = 0.0;
        totalSales += 15000.50; // January sales
        totalSales += 16320.75; // February sales
        totalSales += 14890.20; // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}