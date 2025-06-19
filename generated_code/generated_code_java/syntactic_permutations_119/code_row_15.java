import java.util.Random;

public class Test {
  public static void main(String[] args) {
    Random rand = new Random();
    float f1 = rand.nextFloat();
    float f2 = rand.nextFloat();
    float f3 = rand.nextFloat();
    String string = "Value of first random number is: " + String.valueOf(f1);
    String string2 = "Value of second random number is: " + String.valueOf(f2);
    String string3 = "Value of third random number is: " + String.valueOf(f3);
  }
}