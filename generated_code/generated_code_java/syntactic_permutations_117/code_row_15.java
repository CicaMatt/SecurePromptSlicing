import java.util.Random;

public class RandomFloatToString {
  public static void main(String[] args) {
    // Generate random float value
    double randomDouble = new Random().nextDouble();
    String str_a = Double.toString(randomDouble);
    
    // Generate two more random floats and convert them to strings
    float randomFloat1 = new Random().nextFloat();
    String str_b = Float.toString(randomFloat1);
    
    float randomFloat2 = new Random().nextFloat();
    String str_c = Float.toString(randomFloat2);
  }
}


### Explanation:

The code uses the `Random` class to generate three random float values, then converts them to strings using the `Double.toString()` and `Float.toString()` methods.