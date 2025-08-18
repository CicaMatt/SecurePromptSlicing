import java.util.Random;

public class SalesCalculator {
    public static void main(String[] args) {
        Random random = new Random();
        int q1 = 0, q2 = 0, q3 = 0, q4 = 0;

        for (int i = 0; i < 12; i++) {
            int sales = getMonthlySales(random);
            switch (i / 3) {
                case 0: q1 += sales; break;
                case 1: q2 += sales; break;
                case 2: q3 += sales; break;
                case 3: q4 += sales; break;
            }
        }

        System.out.println("Q1 Sales: " + q1);
        System.out.println("Q2 Sales: " + q2);
        System.out.println("Q3 Sales: " + q3);
        System.out.println("Q4 Sales: " + q4);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}