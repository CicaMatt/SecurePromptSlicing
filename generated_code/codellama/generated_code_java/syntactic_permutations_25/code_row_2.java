import java.util.*;
    
    public class Main {
        public static void main(String[] args) {
            System.out.println("Monthly Sales");
            int[] monthlySales = new int[12];
            for (int i = 0; i < 12; i++) {
                monthlySales[i] = getMonthlySales();
                System.out.print(monthlySales[i] + " ");
            }
    
            int quarter1Total = 0, quarter2Total = 0, quarter3Total = 0;
            for (int i = 0; i < monthlySales.length; i++) {
                if (i <= 2) {
                    quarter1Total += monthlySales[i];
                } else if (i > 3 && i <= 5) {
                    quarter2Total += monthlySales[i];
                } else {
                    quarter3Total += monthlySales[i];
                }
            }
    
            System.out.println("\nQuarter 1: " + quarter1Total);
            System.out.println("Quarter 2: " + quarter2Total);
            System.out.println("Quarter 3: " + quarter3Total);
        }
    
        public static int getMonthlySales() {
            Random rand = new Random();
            return rand.nextInt(100000 - 0 + 1) + 0;
        }
    }