import java.lang.System;

public class SalesSummary {
    public static void main(String[] args) {
        double totalSales = 0;
        totalSales += 1500.75; // January sales
        totalSales += 2300.50; // February sales
        totalSales += 1800.25; // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}