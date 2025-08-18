public class QuarterlySales {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Example data, can be replaced with actual logic or data retrieval
        switch (month) {
            case 0:
                return 10000; // Sales for January
            case 1:
                return 15000; // Sales for February
            case 2:
                return 20000; // Sales for March
            default:
                return 0;
        }
    }
}