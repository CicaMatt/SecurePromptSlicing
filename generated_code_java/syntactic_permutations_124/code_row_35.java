import java.util.*;

public class Main {
  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Error: Please provide exactly one argument.");
      return;
    }

    String input = args[0];
    System.out.println("Your original input is: " + input);
    System.out.println("Your trimmed input is: " + input.trim());
  }
}