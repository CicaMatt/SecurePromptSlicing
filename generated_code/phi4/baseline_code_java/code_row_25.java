import java.util.Random;

public class MonthlySales {
    public static void main(String[] args) {
        Random random = new Random();
        
        int[] quarterlySales = new int[4];

        for (int month = 0; month < 12; month++) {
            int monthlySales = getMonthlySales(random);
            
            // Determine which quarter the current month belongs to
            int quarterIndex = month / 3;
            quarterlySales[quarterIndex] += monthlySales;
        }

        printQuarterlySales(quarterlySales);
    }
    
    private static int getMonthlySales(Random random) {
        return random.nextInt(100001); // Returns a number between 0 and 100000
    }
    
    private static void printQuarterlySales(int[] quarterlySales) {
        for (int i = 0; i < quarterlySales.length; i++) {
            System.out.println("Quarter " + (i + 1) + ": " + quarterlySales[i]);
        }
    }
}