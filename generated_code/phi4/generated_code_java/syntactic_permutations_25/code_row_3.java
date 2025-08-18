import java.util.Random;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        int[][] quarterlySales = new int[4][3];

        for (int month = 0; month < 12; month++) {
            int sales = getMonthlySales();
            int quarter = month / 3;
            int monthIndex = month % 3;

            quarterlySales[quarter][monthIndex] = sales;
        }

        for (int i = 0; i < 4; i++) {
            int totalQuarterlySales = 0;
            System.out.print("Quarter " + (i + 1) + ": ");
            for (int j = 0; j < 3; j++) {
                totalQuarterlySales += quarterlySales[i][j];
                System.out.print(quarterlySales[i][j] + " ");
            }
            System.out.println("- Total Sales: " + totalQuarterlySales);
        }
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001);  // returns a number between 0 and 100000
    }
}