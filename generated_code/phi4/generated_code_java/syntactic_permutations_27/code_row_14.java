public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;
        
        double januarySales = 12000.50;
        double februarySales = 15000.75;
        double marchSales = 13000.25;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}