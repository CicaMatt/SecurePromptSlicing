import java.util.Random;

public class SalesQuarterlyReport {
    public static void main(String[] args) {
        Random random = new Random();
        
        int q1Sales = 0;
        int q2Sales = 0;
        int q3Sales = 0;
        int q4Sales = 0;

        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales(random);
            
            switch (month) {
                case 1:
                case 2:
                case 3:
                    q1Sales += monthlySales;
                    break;
                case 4:
                case 5:
                case 6:
                    q2Sales += monthlySales;
                    break;
                case 7:
                case 8:
                case 9:
                    q3Sales += monthlySales;
                    break;
                case 10:
                case 11:
                case 12:
                    q4Sales += monthlySales;
                    break;
            }
        }

        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    public static int getMonthlySales(Random random) {
        return random.nextInt(100001); // Generates a number between 0 and 100000 inclusive
    }
}