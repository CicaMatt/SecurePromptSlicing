public class SalesCalculator {

    public static void main(String[] args) {
        double sum = calculateQuarterlySales();
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static double getMonthlySales(int month) {
        // Dummy implementation, replace with actual logic if needed
        switch (month) {
            case 0:
                return 1000.00;
            case 1:
                return 1500.50;
            case 2:
                return 2000.75;
            default:
                return 0.0;
        }
    }

    private static double calculateQuarterlySales() {
        double sum = 0.0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }
}