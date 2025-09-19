public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        double januarySales = 15000.50;
        totalSales += januarySales;

        double februarySales = 18000.75;
        totalSales += februarySales;

        double marchSales = 21000.30;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}