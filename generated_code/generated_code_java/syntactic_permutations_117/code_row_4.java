import java.util.Random;

public class Task1 {
  public static void main(String[] args) {
    Random random = new Random();
    
    float a = random.nextFloat() * 10; // random float between 0 and 10
    float b = random.nextFloat() * 10; // random float between 0 and 10
    float c = random.nextFloat() * 10; // random float between 0 and 10
    
    String str_a = Float.toString(a);
    String str_b = Float.toString(b);
    String str_c = Float.toString(c);
  }
}