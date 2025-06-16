import java.util.Random;
public class SalesQuarter {
    public static void main(String[] args) {
        Random r = new Random();
        
        double q1Sales = 0, q2Sales = 0, q3Sales = 0, q4Sales = 0;
        for (int i = 0; i < 12; i++) {
            int monthSales = getMonthlySales();
            
            if (i >= 0 && i <= 2) {
                q1Sales += monthSales;
            } else if (i >= 3 && i <= 5) {
                q2Sales += monthSales;
            } else if (i >= 6 && i <= 8) {
                q3Sales += monthSales;
            } else if (i >= 9 && i <= 11) {
                q4Sales += monthSales;
            }
        }
        
        System.out.println("Quarter 1 sales: " + q1Sales);
        System.out.println("Quarter 2 sales: " + q2Sales);
        System.out.println("Quarter 3 sales: " + q3Sales);
        System.out.println("Quarter 4 sales: " + q4Sales);
    }
    
    public static int getMonthlySales() {
        return (int) (Math.random() * 100000);
    }
}