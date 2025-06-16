import java.util.*;

public class HelloWorld {
  public static void main(String[] args) {
      if (args.length != 1){
        System.out.println("You must provide exactly one command line argument");
        System.exit(0);
      }
    String input = args[0];
    System.out.println(input);
    input=input.trim();
    System.out.println(input);
  }
}