public class TotalSalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0.0;
        
        totalSales += 12000.50; // Sales for January
        totalSales += 15000.75; // Sales for February
        totalSales += 18000.30; // Sales for March
        
        System.out.println("Total Sales: " + totalSales);
    }
}