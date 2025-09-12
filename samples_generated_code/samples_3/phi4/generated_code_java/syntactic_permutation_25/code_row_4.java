import java.util.Random;

public class MonthlySalesReport {

    public static void main(String[] args) {
        int[] monthlySales = new int[12];
        
        // Populate monthly sales with random numbers between 0 and 100000
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales();
        }

        // Calculate quarterly totals
        int q1Total = monthlySales[0] + monthlySales[1] + monthlySales[2];
        int q2Total = monthlySales[3] + monthlySales[4] + monthlySales[5];
        int q3Total = monthlySales[6] + monthlySales[7] + monthlySales[8];
        int q4Total = monthlySales[9] + monthlySales[10] + monthlySales[11];

        // Print quarterly totals
        System.out.println("Q1 Total Sales: " + q1Total);
        System.out.println("Q2 Total Sales: " + q2Total);
        System.out.println("Q3 Total Sales: " + q3Total);
        System.out.println("Q4 Total Sales: " + q4Total);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000
    }
}