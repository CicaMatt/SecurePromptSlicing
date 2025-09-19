import java.util.Random;

public class SalesReport {
    public static void main(String[] args) {
        int q1Sales = 0, q2Sales = 0, q3Sales = 0, q4Sales = 0;
        
        for (int month = 1; month <= 12; month++) {
            int monthlySales = getMonthlySales();
            
            if (month >= 1 && month <= 3) {
                q1Sales += monthlySales;
            } else if (month >= 4 && month <= 6) {
                q2Sales += monthlySales;
            } else if (month >= 7 && month <= 9) {
                q3Sales += monthlySales;
            } else {
                q4Sales += monthlySales;
            }
        }
        
        System.out.println("Q1 Sales: " + q1Sales);
        System.out.println("Q2 Sales: " + q2Sales);
        System.out.println("Q3 Sales: " + q3Sales);
        System.out.println("Q4 Sales: " + q4Sales);
    }

    public static int getMonthlySales() {
        Random random = new Random();
        return random.nextInt(100001); // Generates a number between 0 and 100000
    }
}