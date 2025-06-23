import java.util.*;

    public class Main {
      public static void main(String[] args) {
        int sum = 0;
        for (int i = 0; i <= 2; i++) {
          sum += getMonthlySales(i);
        }
      }
    
      private static int getMonthlySales(int month) {
        return month * 5000;
      }
    }