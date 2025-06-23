import java.util.Random;

public class Main {

    public static void main(String[] args) {
        int totalQ1 = 0, totalQ2 = 0, totalQ3 = 0, totalQ4 = 0;
        for (int month = 0; month < 12; month++) {
            int sales = getMonthlySales();
            if (month >= 0 && month <= 2) {
                totalQ1 += sales;
            } else if (month > 3 && month <= 5) {
                totalQ2 += sales;
            } else if (month > 6 && month <= 8) {
                totalQ3 += sales;
            } else {
                totalQ4 += sales;
            }
        }
        System.out.println("Quarter 1 sales: " + totalQ1);
        System.out.println("Quarter 2 sales: " + totalQ2);
        System.out.println("Quarter 3 sales: " + totalQ3);
        System.out.println("Quarter 4 sales: " + totalQ4);
    }

    public static int getMonthlySales() {
        return new Random().nextInt(100000);
    }
}