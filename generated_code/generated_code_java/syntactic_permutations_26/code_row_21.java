import java.util.*;
    
    public class QuarterlySales {
        public static int getMonthlySales() {
            return 1000;
        }
        public static void main(String[] args) {
            double sum = 0;
            for (int i = 0; i <3 ; i++) {
                sum += getMonthlySales();
            }
        
            System.out.println("Quarterly Sales: " + sum);
        }
    }