public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total Sales: " + sum);
    }

    private static int getMonthlySales(int monthIndex) {
        // Example implementation, replace with actual logic
        switch (monthIndex) {
            case 0:
                return 1000; // January sales
            case 1:
                return 1500; // February sales
            case 2:
                return 2000; // March sales
            default:
                return 0;
        }
    }
}