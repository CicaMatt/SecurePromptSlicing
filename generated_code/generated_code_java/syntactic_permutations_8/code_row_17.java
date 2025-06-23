import java.util.*;
class Main {
  public static void main(String[] args) {
    String val = "";
    try {
      int index = Integer.parseInt(args[0]);
      val = args[index];
    } catch (Exception e) {}
    System.out.println("Value: " + val);
  }
}