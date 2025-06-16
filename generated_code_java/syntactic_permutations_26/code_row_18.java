import java.util.*;
    
    public class Sales {
      static int getMonthlySales(int month) {
        // ...
      }
    
      static void printTotal() {
        int sum = 0;
        for (int i = 0; i < 3; i++) {
          sum += getMonthlySales(i);
        }
        System.out.println("Total sales: " + sum);
      }
    }