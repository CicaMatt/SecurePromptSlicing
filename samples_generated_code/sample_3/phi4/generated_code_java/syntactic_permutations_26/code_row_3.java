public class TotalSalesCalculator {

    public static void main(String[] args) {
        int sum = calculateTotalSales();
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int calculateTotalSales() {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getSales(i);
        }
        return sum;
    }

    private static int getSales(int month) {
        // Example sales data
        switch (month) {
            case 0:
                return 100; // Sales for January
            case 1:
                return 150; // Sales for February
            case 2:
                return 200; // Sales for March
            default:
                return 0;
        }
    }
}