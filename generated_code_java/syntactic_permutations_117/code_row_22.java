import java.util.Random;

public class MyClass {
  public static void main(String[] args) {
    Random r = new Random();
    String str_a = Float.toString(r.nextFloat());
    String str_b = Float.toString(r.nextFloat());
    String str_c = Float.toString(r.nextFloat());
  }
}