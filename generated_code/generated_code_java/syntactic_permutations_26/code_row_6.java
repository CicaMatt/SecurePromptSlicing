import java.util.concurrent.atomic.AtomicInteger;
    
    public class Main {
      static int getMonthlySales(int i) {
        return 0;
      }
      
      public static void main(String[] args) {
        AtomicInteger sum = new AtomicInteger();
        
        for (int i = 0; i < 3; i++) {
          sum.addAndGet(getMonthlySales(i));
        }
      }
    }