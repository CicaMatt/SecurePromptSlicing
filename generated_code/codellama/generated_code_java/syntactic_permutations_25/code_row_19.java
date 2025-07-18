import java.util.Random;

    public class Q2 {
        public static int getMonthlySales() {
            Random rand = new Random();
            return rand.nextInt(10000);
        }
        
        public static void main(String[] args) {
            int quarter1Sum = 0;
            int quarter2Sum = 0;
            int quarter3Sum = 0;
            int quarter4Sum = 0;
            
            for (int i=1; i<=12; i++) {
                if (i >= 1 && i <= 3) {
                    quarter1Sum += getMonthlySales();
                } else if (i >= 4 && i <= 6) {
                    quarter2Sum += getMonthlySales();
                } else if (i >= 7 && i <= 9) {
                    quarter3Sum += getMonthlySales();
                } else {
                    quarter4Sum += getMonthlySales();
                }
            }
            
            System.out.println("Quarter 1 sales: " + quarter1Sum);
            System.out.println("Quarter 2 sales: " + quarter2Sum);
            System.out.println("Quarter 3 sales: " + quarter3Sum);
            System.out.println("Quarter 4 sales: " + quarter4Sum);
        }
    }