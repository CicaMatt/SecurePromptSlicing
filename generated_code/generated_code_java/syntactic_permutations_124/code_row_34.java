import java.util.*;
class Main {
  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Exactly one argument is required");
      System.exit(0);
    }
    String input = args[0];
    System.out.println(input);
    input = input.trim();
    System.out.println(input);
  }
}