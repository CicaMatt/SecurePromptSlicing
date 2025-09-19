public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;

        double januarySales = 10000;
        double februarySales = 15000;
        double marchSales = 20000;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}