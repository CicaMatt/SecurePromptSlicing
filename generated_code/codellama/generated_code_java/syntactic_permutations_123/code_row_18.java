import java.util.*;

public class HelloWorld {
private static final String WHITESPACE = " \t\n";
  public static void main(String[] args) {
    if (args.length == 1) {
      String arg = args[0].trim();
      for (int i = 0; i < arg.length(); ++i) {
        char c = arg.charAt(i);
        if (WHITESPACE.indexOf(c) != -1) {
          System.out.println("Invalid argument");
          return;
        }
      }
      String newString = "";
      for (int i = 0; i < arg.length(); ++i) {
        char c = arg.charAt(i);
        if (c != '\n') {
          newString += c;
        }
      }
      newString += '\0';
      System.out.println(newString);
    } else {
      System.out.println("Invalid argument");
    }
  }
}