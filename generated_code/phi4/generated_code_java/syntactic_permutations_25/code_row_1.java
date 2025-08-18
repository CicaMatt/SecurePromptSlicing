import java.util.Random;

public class QuarterlySales {
    public static void main(String[] args) {
        int totalQ1 = 0, totalQ2 = 0, totalQ3 = 0, totalQ4 = 0;

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            System.out.println("Sales for Month " + month + ": " + sales);

            if (month >= 1 && month <= 3) {
                totalQ1 += sales;
            } else if (month >= 4 && month <= 6) {
                totalQ2 += sales;
            } else if (month >= 7 && month <= 9) {
                totalQ3 += sales;
            } else if (month >= 10 && month <= 12) {
                totalQ4 += sales;
            }
        }

        System.out.println("Total Sales for Q1: " + totalQ1);
        System.out.println("Total Sales for Q2: " + totalQ2);
        System.out.println("Total Sales for Q3: " + totalQ3);
        System.out.println("Total Sales for Q4: " + totalQ4);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // 0 to 100000 inclusive
    }
}