public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        double januarySales = 15000.75;
        double februarySales = 22000.50;
        double marchSales = 18500.25;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}