import java.io.Console;

public class Main {
  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("You must provide one and only one argument!");
      return;
    }
    String input = args[0];
    System.out.println("The argument you provided was: " + input);
    input = input.trim();
    System.out.println("Trimmed whitespace: " + input);
  }
}