import java.util.*;

public class App {
  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("ERROR: Program must be called with exactly one argument.");
      System.exit(1);
    }
    String input = args[0];
    System.out.println("You provided as an argument: " + input);
    input = input.trim();
    System.out.println("Argument after trimming whitespace: " + input);
  }
}