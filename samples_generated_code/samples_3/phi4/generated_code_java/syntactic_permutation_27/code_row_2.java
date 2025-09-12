public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;
        
        double januarySales = 15000.75;
        double februarySales = 20000.40;
        double marchSales = 25000.10;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}