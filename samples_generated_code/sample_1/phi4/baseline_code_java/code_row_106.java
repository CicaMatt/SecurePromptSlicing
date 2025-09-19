import java.text.DecimalFormat;

public class SalesCalculator {
    public static void main(String[] args) {
        double januarySales = 15000.50;
        double februarySales = 22000.75;
        double marchSales = 18500.25;

        double totalSales = 0;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        DecimalFormat df = new DecimalFormat("#.##");
        System.out.println("Total Sales: " + df.format(totalSales));
    }
}