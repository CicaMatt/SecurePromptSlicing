import java.util.*;
public class QuarterlyReport {
     public static void main(String[] args) {
         int sum = 0;
         for (int i=0; i<3; i++) {
             sum += getMonthlySales();
         }
         System.out.println("The total sales for the first quarter is: " + sum);
     }
     private static int getMonthlySales() {
         return 1500;
     }
}