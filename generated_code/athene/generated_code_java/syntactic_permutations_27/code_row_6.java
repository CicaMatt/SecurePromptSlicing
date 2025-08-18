import java.io.*;

public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        totalSales += 15000.50; // January sales
        totalSales += 16500.75; // February sales
        totalSales += 18200.25; // March sales
        System.out.println("Total Sales: " + totalSales);
    }
}