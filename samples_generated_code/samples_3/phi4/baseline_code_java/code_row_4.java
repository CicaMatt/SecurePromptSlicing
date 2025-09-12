public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Dummy implementation of monthly sales
        switch (month) {
            case 0:
                return 100; // Sales for January
            case 1:
                return 150; // Sales for February
            case 2:
                return 200; // Sales for March
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }
}