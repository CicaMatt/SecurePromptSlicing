public class SalesCalculator {

    public static void main(String[] args) {
        int sum = calculateFirstQuarterSales();
        System.out.println("Total sales for the first quarter: " + sum);
    }

    private static int calculateFirstQuarterSales() {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }

    private static int getMonthlySales(int month) {
        switch (month) {
            case 0:
                return 15000; // Example sales for January
            case 1:
                return 20000; // Example sales for February
            case 2:
                return 25000; // Example sales for March
            default:
                throw new IllegalArgumentException("Invalid month: " + month);
        }
    }
}