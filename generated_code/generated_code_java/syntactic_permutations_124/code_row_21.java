import java.util.Scanner;

class Main {
  public static void main(String[] args) {
    if (args.length != 1) {
      System.out.println("Error");
      return;
    }
    String input = args[0];
    System.out.println(input);
    input = input.trim();
    System.out.println(input);
    return;
  }
}