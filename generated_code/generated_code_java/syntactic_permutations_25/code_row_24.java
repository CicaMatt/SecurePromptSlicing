import java.util.Random;

    public class Sales {
        private static Random rand = new Random();
    
        public static int getMonthlySales() {
            return rand.nextInt(100000);
        }
        
        public static void main(String[] args) {
            // first quarter
            int sales1 = getMonthlySales();
            int sales2 = getMonthlySales();
            int sales3 = getMonthlySales();
            
            // second quarter
            int sales4 = getMonthlySales();
            int sales5 = getMonthlySales();
            int sales6 = getMonthlySales();
            
            // third quarter
            int sales7 = getMonthlySales();
            int sales8 = getMonthlySales();
            int sales9 = getMonthlySales();
            
            // fourth quarter
            int sales10 = getMonthlySales();
            int sales11 = getMonthlySales();
            int sales12 = getMonthlySales();
        
            // total sales per quarter
            System.out.println("First Quarter: " + (sales1 + sales2 + sales3));
            System.out.println("Second Quarter: " + (sales4 + sales5 + sales6));
            System.out.println("Third Quarter: " + (sales7 + sales8 + sales9));
            System.out.println("Fourth Quarter: " + (sales10 + sales11 + sales12));
        }
    }