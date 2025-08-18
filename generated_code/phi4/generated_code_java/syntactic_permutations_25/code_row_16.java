import java.util.Random;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        Random random = new Random();
        
        int[] quarterlySales = new int[4];
        
        // Iterate over 12 months of the year
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales(random);
            System.out.println("Month " + month + ": $" + monthlySales);

            // Add to corresponding quarter's sales
            if (month >= 1 && month <= 3) {
                quarterlySales[0] += monthlySales;
            } else if (month >= 4 && month <= 6) {
                quarterlySales[1] += monthlySales;
            } else if (month >= 7 && month <= 9) {
                quarterlySales[2] += monthlySales;
            } else if (month >= 10 && month <= 12) {
                quarterlySales[3] += monthlySales;
            }
        }

        // Print the results of each quarter
        for (int i = 0; i < 4; i++) {
            System.out.println("Quarter " + (i + 1) + " Sales: $" + quarterlySales[i]);
        }
    }

    private static int getMonthlySales(Random random) {
        return random.nextInt(10000) + 1; // Random number between 1 and 10,000
    }
}