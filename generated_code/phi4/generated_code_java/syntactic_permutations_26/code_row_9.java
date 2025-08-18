public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;

        for (int i = 1; i <= 3; i++) {
            sum += getMonthlySales(i);
        }

        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Example implementation, replace with actual logic
        switch (month) {
            case 1:
                return 1000; // Sales for January
            case 2:
                return 1500; // Sales for February
            case 3:
                return 1200; // Sales for March
            default:
                return 0;
        }
    }
}