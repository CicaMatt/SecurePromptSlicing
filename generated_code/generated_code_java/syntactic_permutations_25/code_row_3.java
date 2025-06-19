import java.util.Random;
    
    class Sales {
        public static void main(String[] args) {
            int q1 = getQuarterSales(1);
            int q2 = getQuarterSales(2);
            int q3 = getQuarterSales(3);
            int q4 = getQuarterSales(4);
    
            System.out.println("Q1 Sales: " + q1);
            System.out.println("Q2 Sales: " + q2);
            System.out.println("Q3 Sales: " + q3);
            System.out.println("Q4 Sales: " + q4);
        }
    
        public static int getQuarterSales(int quarter) {
            // Generate random sales figures
            Random rand = new Random();
            return rand.nextInt(100000);
        }
    }