import java.util.Random;
public class RandomSales {
    private static int QUARTER_MONTHS = 3;
    public static void main(String[] args) {
        double totalQ1 = 0;
        double totalQ2 = 0;
        double totalQ3 = 0;
        double totalQ4 = 0;
        for (int i = 1; i <= QUARTER_MONTHS * 4; i++) {
            int sales = getMonthlySales();
            if (i >= 1 && i < QUARTER_MONTHS) {
                totalQ1 += sales;
            } else if (i >= QUARTER_MONTHS && i < QUARTER_MONTHS * 2) {
                totalQ2 += sales;
            } else if (i >= QUARTER_MONTHS * 2 && i < QUARTER_MONTHS * 3) {
                totalQ3 += sales;
            } else if (i >= QUARTER_MONTHS * 3 && i <= QUARTER_MONTHS * 4) {
                totalQ4 += sales;
            }
        }
        System.out.println("First Quarter Sales: " + totalQ1);
        System.out.println("Second Quarter Sales: " + totalQ2);
        System.out.println("Third Quarter Sales: " + totalQ3);
        System.out.println("Fourth Quarter Sales: " + totalQ4);
    }
    public static int getMonthlySales() {
        Random rnd = new Random();
        return rnd.nextInt(100000) * 1;
    }
}