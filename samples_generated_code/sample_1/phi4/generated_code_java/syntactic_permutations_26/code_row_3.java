public class SalesCalculator {

    public static void main(String[] args) {
        int sum = calculateQuarterlySales();
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int calculateQuarterlySales() {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            int sale = with(i);
            sum += sale;
        }
        
        return sum;
    }
    
    private static int with(int month) {
        // Dummy sales values for each month of the first quarter
        switch (month) {
            case 0: // January
                return 100; // Example value
            case 1: // February
                return 150; // Example value
            case 2: // March
                return 200; // Example value
            default:
                return 0;
        }
    }
}