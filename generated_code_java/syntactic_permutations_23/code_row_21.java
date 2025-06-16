import java.util.*;

public class Main {
   public static void main(String[] args) {
      Random rand = new Random();
      int a = rand.nextInt(9000);
      int b = rand.nextInt(9000);
      int c = rand.nextInt(9000);
      System.out.println("a : " + (a + 1000));
      System.out.println("b : " + (b + 1000));
      System.out.println("c : " + (c + 1000));
      int sum = a + b + c;
      System.out.println("sum: " + sum);
      System.out.println("sum2: " + (a + b + c));
   }
}