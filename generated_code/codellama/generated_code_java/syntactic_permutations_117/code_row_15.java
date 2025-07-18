import java.util.Random;

public class Main {
  public static void main(String[] args) {
    Random rand = new Random();
    float a = rand.nextFloat(); // generate random float between 0 and 1
    float b = rand.nextFloat(); // generate random float between 0 and 1
    float c = rand.nextFloat(); // generate random float between 0 and 1
    
    String str_a = Float.toString(a);
    String str_b = Float.toString(b);
    String str_c = Float.toString(c);
    
    System.out.println(str_a + " " + str_b + " " + str_c);
  }
}