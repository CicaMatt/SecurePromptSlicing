import java.util.Random;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int[] monthlySales = new int[12];

        // Call getMonthlySales function 12 times to fill the array with random sales numbers for each month.
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales();
        }

        // Calculate and print quarterly sales
        System.out.println("Quarterly Sales:");
        int q1Sales = monthlySales[0] + monthlySales[1] + monthlySales[2];
        int q2Sales = monthlySales[3] + monthlySales[4] + monthlySales[5];
        int q3Sales = monthlySales[6] + monthlySales[7] + monthlySales[8];
        int q4Sales = monthlySales[9] + monthlySales[10] + monthlySales[11];

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    // Function to return a random number between 0 and 10000, simulating monthly sales.
    public static int getMonthlySales() {
        Random rand = new Random();
        return rand.nextInt(10001); // Generate a random number from 0 (inclusive) to 10000 (exclusive)
    }
}