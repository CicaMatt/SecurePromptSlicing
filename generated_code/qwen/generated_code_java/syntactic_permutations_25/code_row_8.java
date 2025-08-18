import java.util.Random;

public class SalesCalculator {

    public static void main(String[] args) {
        int[] quarterlySales = new int[4];
        
        Random random = new Random();
        
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales(random);
            if (month <= 3) {
                quarterlySales[0] += monthlySales;
            } else if (month <= 6) {
                quarterlySales[1] += monthlySales;
            } else if (month <= 9) {
                quarterlySales[2] += monthlySales;
            } else {
                quarterlySales[3] += monthlySales;
            }
        }

        for (int quarter = 0; quarter < 4; quarter++) {
            System.out.println("Quarter " + (quarter + 1) + " Sales: " + quarterlySales[quarter]);
        }
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}