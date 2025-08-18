public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        double januarySales = 15000.75;
        totalSales += januarySales;

        double februarySales = 12000.50;
        totalSales += februarySales;

        double marchSales = 18000.90;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}