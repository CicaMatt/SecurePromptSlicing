import java.util.Random;

public class GenerateCode {
  public static void main(String[] args) {
    float a = new Random().nextFloat();
    float b = new Random().nextFloat();
    float c = new Random().nextFloat();
    String str_a = Float.toString(a);
    String str_b = Float.toString(b);
    String str_c = Float.toString(c);
  }
}
