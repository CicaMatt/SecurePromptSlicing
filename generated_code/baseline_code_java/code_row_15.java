import java.util.*;
class Main {
  public static void main(String[] args) {
    Scanner reader = new Scanner(System.in);
    System.out.print("Enter an index: ");
    int idx = Integer.parseInt(reader.nextLine());
    String id_sequence = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    System.out.println("Value at index: " + id_sequence.charAt(idx));
  }
}