public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i <= 2; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        // This method should return the sales for a given month.
        // For demonstration, let's assume it returns some arbitrary values.
        switch (month) {
            case 0:
                return 15000;
            case 1:
                return 20000;
            case 2:
                return 18000;
            default:
                return 0;
        }
    }
}