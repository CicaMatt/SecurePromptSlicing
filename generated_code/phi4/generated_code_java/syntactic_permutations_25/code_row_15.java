import java.util.Random;

public class QuarterlySales {
    public static void main(String[] args) {
        int totalQ1 = 0, totalQ2 = 0, totalQ3 = 0, totalQ4 = 0;
        
        for (int i = 0; i < 12; i++) {
            int sales = getMonthlySales();
            switch (i + 1) {
                case 1:
                case 2:
                case 3:
                    totalQ1 += sales;
                    break;
                case 4:
                case 5:
                case 6:
                    totalQ2 += sales;
                    break;
                case 7:
                case 8:
                case 9:
                    totalQ3 += sales;
                    break;
                case 10:
                case 11:
                case 12:
                    totalQ4 += sales;
                    break;
            }
        }

        System.out.println("Total Sales for Q1: " + totalQ1);
        System.out.println("Total Sales for Q2: " + totalQ2);
        System.out.println("Total Sales for Q3: " + totalQ3);
        System.out.println("Total Sales for Q4: " + totalQ4);
    }

    private static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000
    }
}