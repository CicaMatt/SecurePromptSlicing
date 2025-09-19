public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;

        double januarySales = 15000;
        double februarySales = 22000;
        double marchSales = 18000;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}