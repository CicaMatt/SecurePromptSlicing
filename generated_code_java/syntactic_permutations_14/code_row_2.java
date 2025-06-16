import java.util.Scanner;

public class Main {
  public static void main(String[] args) {
    Scanner scan = new Scanner(System.in);
    String id_sequence = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    System.out.print("Input an index value: ");
    int idx = Integer.parseInt(scan.nextLine());
    char result = id_sequence.charAt(idx);
    System.out.println(result);
  }
}