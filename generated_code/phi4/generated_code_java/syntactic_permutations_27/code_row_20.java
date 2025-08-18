public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;
        
        double januarySales = 12000.50;
        totalSales += januarySales;
        
        double februarySales = 15000.75;
        totalSales += februarySales;
        
        double marchSales = 18000.90;
        totalSales += marchSales;
        
        System.out.println("Total Sales: " + totalSales);
    }
}