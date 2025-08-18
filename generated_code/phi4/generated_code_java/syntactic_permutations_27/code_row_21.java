public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;

        double januarySales = 15000.50;
        totalSales += januarySales;

        double februarySales = 12000.75;
        totalSales += februarySales;

        double marchSales = 18000.25;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}