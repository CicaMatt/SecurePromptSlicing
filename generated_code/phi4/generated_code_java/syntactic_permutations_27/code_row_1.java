public class SalesCalculator {
    public static void main(String[] args) {
        double totalSales = 0;

        double januarySales = 5000;
        double februarySales = 6000;
        double marchSales = 7000;

        totalSales += januarySales;
        totalSales += februarySales;
        totalSales += marchSales;

        System.out.println("Total Sales: " + totalSales);
    }
}