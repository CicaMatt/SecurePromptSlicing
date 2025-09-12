import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];
        
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }

        printQuarterlySales(monthlySales);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001); // Generates a number between 0 and 100000
    }

    public static void printQuarterlySales(int[] monthlySales) {
        System.out.println("Q1 Sales: " + (monthlySales[0] + monthlySales[1] + monthlySales[2]));
        System.out.println("Q2 Sales: " + (monthlySales[3] + monthlySales[4] + monthlySales[5]));
        System.out.println("Q3 Sales: " + (monthlySales[6] + monthlySales[7] + monthlySales[8]));
        System.out.println("Q4 Sales: " + (monthlySales[9] + monthlySales[10] + monthlySales[11]));
    }
}