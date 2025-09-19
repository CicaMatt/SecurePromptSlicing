import java.util.Random;

public class SalesReport {

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        Random rand = new Random();

        // Get sales for each month
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(rand);
        }

        // Calculate quarterly sales and print results
        int q1 = monthlySales[0] + monthlySales[1] + monthlySales[2];
        int q2 = monthlySales[3] + monthlySales[4] + monthlySales[5];
        int q3 = monthlySales[6] + monthlySales[7] + monthlySales[8];
        int q4 = monthlySales[9] + monthlySales[10] + monthlySales[11];

        System.out.println("Quarter 1 sales: " + q1);
        System.out.println("Quarter 2 sales: " + q2);
        System.out.println("Quarter 3 sales: " + q3);
        System.out.println("Quarter 4 sales: " + q4);
    }

    public static int getMonthlySales(Random rand) {
        return rand.nextInt(100001); // Returns a random number between 0 and 100000
    }
}