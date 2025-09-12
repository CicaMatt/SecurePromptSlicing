public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        // Assuming these are the sales amounts for January, February, and March.
        double januarySales = 15000.75;
        double februarySales = 20000.50;
        double marchSales = 25000.25;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;
        
        System.out.println("Total Sales: " + totalSales);
    }
}