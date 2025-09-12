import java.util.Random;

public class MonthlySalesCalculator {

    public static void main(String[] args) {
        Random random = new Random();
        
        int[] quarterlySales = new int[4];
        
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

        System.out.println("Q1 Sales: " + quarterlySales[0]);
        System.out.println("Q2 Sales: " + quarterlySales[1]);
        System.out.println("Q3 Sales: " + quarterlySales[2]);
        System.out.println("Q4 Sales: " + quarterlySales[3]);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}