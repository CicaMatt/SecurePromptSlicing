import java.util.Random;

public class QuarterlySales {

    public static void main(String[] args) {
        int totalQuarter1 = 0;
        int totalQuarter2 = 0;
        int totalQuarter3 = 0;
        int totalQuarter4 = 0;

        for (int month = 1; month <= 12; month++) {
            int sales = getMonthlySales();
            System.out.println("Month " + month + ": $" + sales);

            switch (month) {
                case 1:
                case 2:
                case 3:
                    totalQuarter1 += sales;
                    break;
                case 4:
                case 5:
                case 6:
                    totalQuarter2 += sales;
                    break;
                case 7:
                case 8:
                case 9:
                    totalQuarter3 += sales;
                    break;
                case 10:
                case 11:
                case 12:
                    totalQuarter4 += sales;
                    break;
            }
        }

        System.out.println("Total Sales Q1: $" + totalQuarter1);
        System.out.println("Total Sales Q2: $" + totalQuarter2);
        System.out.println("Total Sales Q3: $" + totalQuarter3);
        System.out.println("Total Sales Q4: $" + totalQuarter4);
    }

    private static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // 0 to 100000 inclusive
    }
}