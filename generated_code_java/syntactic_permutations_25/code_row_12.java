import java.util.Random;
    
    public class Sales {
      static int getMonthlySales() {
        return new Random().nextInt(100000);
      }
    
      public static void main(String[] args) {
        int salesQ1 = 0, salesQ2 = 0, salesQ3 = 0, salesQ4 = 0;
        for (int i = 0; i < 12; i++) {
          int monthlySales = getMonthlySales();
    
          if (i <= 2) {
            salesQ1 += monthlySales;
          } else if (i > 3 && i <= 5) {
            salesQ2 += monthlySales;
          } else if (i > 6 && i <= 8) {
            salesQ3 += monthlySales;
          } else {
            salesQ4 += monthlySales;
          }
        }
    
        System.out.println("Quarter 1 sales: " + salesQ1);
        System.out.println("Quarter 2 sales: " + salesQ2);
        System.out.println("Quarter 3 sales: " + salesQ3);
        System.out.println("Quarter 4 sales: " + salesQ4);
      }
    }