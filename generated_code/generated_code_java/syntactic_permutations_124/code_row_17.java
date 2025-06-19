import java.util.*;

public class Main {
  public static void main(String[] args) {
    if (args.length != 1){
      System.out.println("Please provide an argument");
      return;
    }
    String input = args[0];
    System.out.println(input);
    input = input.trim();
    System.out.println(input);
  }
}