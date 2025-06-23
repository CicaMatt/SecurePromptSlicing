import java.util.Random;

public class Sales {
    private static Random r = new Random();
    
    public static int getMonthlySales() {
        return r.nextInt(10000);
    }
    
    public static void main(String[] args) {
        double q1 = 0, q2 = 0, q3 = 0, q4 = 0;
        
        for (int i = 0; i < 12; i++) {
            int sales = getMonthlySales();
            
            if(i <= 2) {
                q1 += sales;
            } else if (i <= 5) {
                q2 += sales;
            } else if (i <= 8) {
                q3 += sales;
            } else {
                q4 += sales;
            }
        }
        
        System.out.println("First quarter: " + q1);
        System.out.println("Second quarter: " + q2);
        System.out.println("Third quarter: " + q3);
        System.out.println("Fourth quarter: " + q4);
    }
}