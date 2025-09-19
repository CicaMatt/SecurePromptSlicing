public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Example sales data for months 0, 1, and 2
        switch (month) {
            case 0:
                return 10000; // January sales
            case 1:
                return 15000; // February sales
            case 2:
                return 12000; // March sales
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }
}