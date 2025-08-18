public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        double januarySales = 15000.75;
        double februarySales = 12000.50;
        double marchSales = 18000.25;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}