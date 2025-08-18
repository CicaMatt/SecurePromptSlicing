public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        double januarySales = 15000.50;
        double februarySales = 18000.75;
        double marchSales = 21000.90;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}