public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;

        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }

        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int monthIndex) {
        // Sample data, replace with actual logic or data retrieval
        switch (monthIndex) {
            case 0:
                return 1000; // January sales
            case 1:
                return 1500; // February sales
            case 2:
                return 2000; // March sales
            default:
                throw new IllegalArgumentException("Invalid month index");
        }
    }
}