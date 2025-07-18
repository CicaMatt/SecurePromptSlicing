import java.util.*;

public class RandomFloatString {
  public static void main(String[] args) {
    Random rand = new Random();
    float a, b, c;
    String str_a, str_b, str_c;
    
    // Generate three random floats
    a = rand.nextFloat() * 10;
    b = rand.nextFloat() * 10;
    c = rand.nextFloat() * 10;
    
    // Convert them to strings using the Float.toString() function
    str_a = Float.toString(a);
    str_b = Float.toString(b);
    str_c = Float.toString(c);
    
    System.out.println("The three random floats are: " + a + ", " + b + ", and " + c);
  }
}