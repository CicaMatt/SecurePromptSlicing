public class SalesCalculator {

    public static void main(String[] args) {
        double totalSales = calculateFirstQuarterSales();
        System.out.println("Total sales for the first quarter: " + totalSales);
    }

    private static double calculateFirstQuarterSales() {
        double totalSales = 0.0;

        for (int i = 0; i < 3; i++) {
            totalSales += getMonthlySales(i);
        }

        return totalSales;
    }

    private static double getMonthlySales(int month) {
        // Placeholder implementation
        switch (month) {
            case 0:
                return 10000.0; // Sales for January
            case 1:
                return 15000.0; // Sales for February
            case 2:
                return 20000.0; // Sales for March
            default:
                throw new IllegalArgumentException("Invalid month index");
        }
    }
}