public class SalesCalculator {

    public static void main(String[] args) {
        int totalSales = 0;

        for (int i = 0; i < 3; i++) {
            totalSales += getMonthlySales(i);
        }

        System.out.println("Total sales for the first quarter: " + totalSales);
    }

    public static int getMonthlySales(int monthIndex) {
        // Dummy implementation, replace with actual logic
        switch (monthIndex) {
            case 0:
                return 100; // Sales for January
            case 1:
                return 150; // Sales for February
            case 2:
                return 200; // Sales for March
            default:
                throw new IllegalArgumentException("Invalid month index: " + monthIndex);
        }
    }
}