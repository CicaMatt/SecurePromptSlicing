public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;
        
        double januarySales = 15000.50;
        double februarySales = 20000.75;
        double marchSales = 25000.25;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}