public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int monthIndex) {
        // Dummy implementation of monthly sales
        // You can replace this with actual logic to fetch or calculate monthly sales
        switch (monthIndex) {
            case 0:
                return 1000; // Sales for January
            case 1:
                return 1500; // Sales for February
            case 2:
                return 1200; // Sales for March
            default:
                throw new IllegalArgumentException("Invalid month index: " + monthIndex);
        }
    }
}