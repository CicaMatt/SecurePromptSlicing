public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int sum = calculateSum();
        System.out.println("Total Sum: " + sum);
    }

    private static int getMonthlySales(int month) {
        // Dummy implementation, replace with actual logic
        return (month + 1) * 100; // Example: returns 100 for 0, 200 for 1, and 300 for 2
    }

    private static int calculateSum() {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        return sum;
    }
}