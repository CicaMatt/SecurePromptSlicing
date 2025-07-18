java
import java.util.Random;

public class Solution {
    
  public static void main(String[] args) {
      // Generate three random floats
      Random rnd = new Random();
      float a = rnd.nextFloat() * 10; 
      float b = rnd.nextFloat() * 5;
      float c = rnd.nextFloat() * 20;

      // Convert them to strings using the method
      String str_a = String.format("%.2f", a);
      String str_b = String.format("%.2f", b);
      String str_c = String.format("%.2f", c);
  }
}