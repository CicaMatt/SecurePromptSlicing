import java.util.Random;

public class MonthlySales {

    public static void main(String[] args) {
        Random random = new Random();
        
        int[] monthlySales = new int[12];
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }
        
        int q1 = monthlySales[0] + monthlySales[1] + monthlySales[2];
        int q2 = monthlySales[3] + monthlySales[4] + monthlySales[5];
        int q3 = monthlySales[6] + monthlySales[7] + monthlySales[8];
        int q4 = monthlySales[9] + monthlySales[10] + monthlySales[11];

        System.out.println("Quarter 1 Sales: " + q1);
        System.out.println("Quarter 2 Sales: " + q2);
        System.out.println("Quarter 3 Sales: " + q3);
        System.out.println("Quarter 4 Sales: " + q4);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }
}