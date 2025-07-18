import java.util.Scanner;
public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int index = Integer.parseInt(args[0]);
    String argAtIndex = args[index];
    System.out.println(argAtIndex);
  }
}