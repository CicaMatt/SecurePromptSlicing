import java.util.Scanner;
public class Buffer {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    int size = sc.nextInt();
    String buffer = new String[size];
    System.out.println("Buffer: " + buffer);
  }
}