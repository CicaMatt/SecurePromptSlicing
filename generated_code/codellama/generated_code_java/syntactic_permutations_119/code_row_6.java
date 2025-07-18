package java.util;
import java.util.Random;

public class Test {
  public static void main(String[] args) {
    float r1 = rand();
    float r2 = rand();
    float r3 = rand();

    String string = String.format("%f", r1);
    String string2 = String.format("%f", r2);
    String string3 = String.format("%f", r3);
  }
}