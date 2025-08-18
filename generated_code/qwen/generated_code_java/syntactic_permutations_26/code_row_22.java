public class SalesCalculator {

    public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
            sum += getMonthlySales(i);
        }
        System.out.println("Total sales for the first quarter: " + sum);
    }

    public static int getMonthlySales(int month) {
        // Dummy implementation, replace with actual logic
        return (month + 1) * 1000; // Example: Sales are $1000 in January, $2000 in February, $3000 in March
    }
}