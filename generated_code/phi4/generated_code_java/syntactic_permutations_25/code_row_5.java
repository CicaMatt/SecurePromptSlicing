import java.util.Random;

public class MonthlySalesCalculator {
    public static void main(String[] args) {
        Random random = new Random();
        int[] monthlySales = new int[12];
        
        for (int i = 0; i < 12; i++) {
            monthlySales[i] = getMonthlySales(random);
        }

        System.out.println("Q1 Sales: " + quarterlySales(monthlySales, 0));
        System.out.println("Q2 Sales: " + quarterlySales(monthlySales, 3));
        System.out.println("Q3 Sales: " + quarterlySales(monthlySales, 6));
        System.out.println("Q4 Sales: " + quarterlySales(monthlySales, 9));
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001);
    }

    public static int quarterlySales(int[] sales, int startMonth) {
        return sales[startMonth] + sales[startMonth + 1] + sales[startMonth + 2];
    }
}