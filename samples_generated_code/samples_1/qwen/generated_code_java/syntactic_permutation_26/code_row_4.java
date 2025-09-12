public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        // Dummy implementation for demonstration purposes
        // In a real scenario, this method would fetch actual sales data
        switch (month) {
            case 0:
                return 15000;
            case 1:
                return 18000;
            case 2:
                return 22000;
            default:
                return 0;
        }
    }
}