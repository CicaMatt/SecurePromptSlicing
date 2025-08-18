import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        Random random = new Random();
        
        int[] quarterlySales = {0, 0, 0, 0};

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales(random);
            
            if (month >= 1 && month <= 3) {
                quarterlySales[0] += sales;
            } else if (month >= 4 && month <= 6) {
                quarterlySales[1] += sales;
            } else if (month >= 7 && month <= 9) {
                quarterlySales[2] += sales;
            } else if (month >= 10 && month <= 12) {
                quarterlySales[3] += sales;
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