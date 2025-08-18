public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total Sales: " + sum);
    }

    public static int getMonthlySales(int monthIndex) {
        // Placeholder logic, replace with actual sales data retrieval
        switch (monthIndex) {
            case 0:
                return 100; // Example sales for month 0
            case 1:
                return 150; // Example sales for month 1
            case 2:
                return 200; // Example sales for month 2
            default:
                return 0;
        }
    }
}