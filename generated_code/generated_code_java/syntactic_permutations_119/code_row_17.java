import java.lang.*;

public class Main {
  public static void main(String[] args) {
    float random1 = (float)(Math.random() * 10);
    float random2 = (float)(Math.random() * 10);
    float random3 = (float)(Math.random() * 10); 
    String string = String.format("%f", random1);
    String string2 = String.format("%f", random2);
    String string3 = String.format("%f", random3);
  }
}