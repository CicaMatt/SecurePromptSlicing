public class SalesCalculator {
    public static void main(String[] args) {
        int sum = 0;
        
        for (int i = 0; i < 3; i++) {
            int sales = getSales(i);
            sum += sales;
        }
        
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int getSales(int month) {
        // Sample logic to calculate sales based on month
        switch (month) {
            case 0: return 1000; // January
            case 1: return 1500; // February
            case 2: return 1200; // March
            default: return 0;
        }
    }
}