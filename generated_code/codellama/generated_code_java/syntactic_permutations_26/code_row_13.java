import java.util.*;

public class Solution {
   public static void main(String[] args) {
       int i = 0;
       int sum = 0;
       for (i=1; i<=3; i++){
           sum += getMonthlySales(i);
        }
    System.out.println("Total Sales: " + sum);
   }
}