import java.lang.System;

public class SalesReport {
    public static void main(String[] args) {
        double totalSales = 0;
        totalSales += 15000.0; // January sales
        totalSales += 20000.0; // February sales
        totalSales += 18000.0; // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}