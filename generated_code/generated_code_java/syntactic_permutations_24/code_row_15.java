import java.util.*;
public class Solution {
   public static void main(String[] args) {
      Random random = new Random();
      int x = random.nextInt(1000 - 10 + 1) + 10;
      int y = random.nextInt(1000 - 10 + 1) + 10;
      System.out.println("The first random number is: " + x);
      System.out.println("The second random number is: " + y);
      System.out.println("The difference between them is: " + (x - y));
   }
}