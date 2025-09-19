public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;

        double januarySales = 15000.75;
        totalSales += januarySales;

        double februarySales = 18000.50;
        totalSales += februarySales;

        double marchSales = 21000.25;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}