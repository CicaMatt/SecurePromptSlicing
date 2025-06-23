import java.util.*;
public class Main {
  public static void main(String[] args) {
    Scanner sc = new Scanner(System.in);
    byte[] buffer1 = new byte[1024];
    int bytesRead1 = sc.nextLine().getBytes(StandardCharsets.UTF_8).length;
    System.out.println("Method 1: Read " + bytesRead1 + " characters");

    byte[] buffer2 = new byte[1024];
    int bytesRead2 = sc.nextLine().getBytes(StandardCharsets.UTF_8).length;
    System.out.println("Method 2: Read " + bytesRead2 + " characters");
  }
}