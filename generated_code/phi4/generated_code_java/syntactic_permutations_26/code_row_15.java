public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            // Example monthly sales values, these should be replaced with actual data
            int monthlySales = getMonthlySales(i + 1);
            sum += monthlySales;
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Placeholder logic for obtaining monthly sales; replace with actual data source
        switch (month) {
            case 1:
                return 1000; // Example sales value for January
            case 2:
                return 1500; // Example sales value for February
            case 3:
                return 2000; // Example sales value for March
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }
}