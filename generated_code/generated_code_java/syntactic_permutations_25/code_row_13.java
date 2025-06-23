import java.util.Random;

    public class Sales {

        private static Random rand = new Random();

        private int getMonthlySales() {
            return rand.nextInt(100000);
        }
    
        public static void main(String[] args) {
            int salesQ1 = 0;
            for (int i=1; i<4; i++) {
                Sales s = new Sales();
                salesQ1 += s.getMonthlySales();
            }
    
            System.out.println("Quarter 1: " + salesQ1);
        }
    }